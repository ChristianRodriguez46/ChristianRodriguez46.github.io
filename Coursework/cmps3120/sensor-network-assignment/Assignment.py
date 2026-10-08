import numpy as np
import matplotlib.pyplot as plt
import sys
from scipy.spatial import Voronoi, voronoi_plot_2d
from scipy.spatial.distance import cdist
from scipy.spatial import KDTree, ConvexHull
from collections import deque
import random

# Function to get dynamic low-end nodes count from command line
def get_dynamic_low_end_nodes():
    try:
        # Try to get the first command-line argument as the number of low-end nodes
        return int(sys.argv[1])  # Get the number of low-end nodes from command line
    except IndexError:
        # If no argument is provided, use the default value
        print("Using default number of low-end nodes: 50")
        return 50  # Default to 50 if no argument is provided

# -------------------------------
# Part 1: Implementing the Voronoi Diagram with Random Initial Assignment
# -------------------------------

# Set a random seed for reproducibility
np.random.seed(42)

# Define the number of cluster heads (CH) and low-end (LE) nodes
num_ch = 5      # Number of cluster heads
num_le = get_dynamic_low_end_nodes()  # Number of low-end nodes dynamically
area_size = 100  # Size of the area (100x100 units)

# Generate random positions for cluster heads and low-end nodes within the area
ch_positions = np.random.rand(num_ch, 2) * area_size
le_positions = np.random.rand(num_le, 2) * area_size

# Generate Voronoi Diagram based on cluster heads' positions
vor = Voronoi(ch_positions)

# Randomly assign each low-end node to a cluster head
le_assignments_initial = np.random.randint(0, num_ch, num_le)

# Build initial clusters: a dictionary where each key is a cluster head index
clusters_initial = {i: [] for i in range(num_ch)}
for i, assignment in enumerate(le_assignments_initial):
    # Append the low-end node index to the corresponding cluster head's list
    clusters_initial[assignment].append(i)

# -------------------------------
# Data Collection: Calculate Hop Counts
# -------------------------------

# Build Connectivity Graph Based on Communication Range
communication_range = 30  # Maximum distance for nodes to communicate directly

# Combine cluster heads and low-end nodes into one array of positions
all_positions = np.vstack((ch_positions, le_positions))
num_nodes = num_ch + num_le  # Total number of nodes

# Initialize adjacency matrix to represent connectivity between nodes
adjacency_matrix = np.zeros((num_nodes, num_nodes), dtype=int)

# Calculate pairwise distances between all nodes (precompute for efficiency)
pairwise_distances = cdist(all_positions, all_positions, 'euclidean')

# Build adjacency matrix: nodes are connected if within communication range
for i in range(num_nodes):
    for j in range(i + 1, num_nodes):
        if pairwise_distances[i, j] <= communication_range:
            adjacency_matrix[i, j] = 1  # Mark as connected
            adjacency_matrix[j, i] = 1  # Undirected graph, so symmetric

# Function to calculate hop count from a node to a cluster head using BFS
def calculate_hop_count(node_index, ch_index, adjacency_matrix):
    visited = [False] * num_nodes  # Keep track of visited nodes
    queue = deque()
    queue.append((node_index, 0))  # Start from the node with 0 hops
    visited[node_index] = True  # Mark the starting node as visited

    while queue:
        current_node, hops = queue.popleft()  # Dequeue the next node
        if current_node == ch_index:
            return hops  # Reached the cluster head, return hop count
        # Explore neighbors
        for neighbor in range(num_nodes):
            if adjacency_matrix[current_node, neighbor] == 1 and not visited[neighbor]:
                visited[neighbor] = True  # Mark neighbor as visited
                queue.append((neighbor, hops + 1))  # Enqueue neighbor with incremented hop count
    return np.inf  # No path found to cluster head

# Calculate initial hop counts from each low-end node to its assigned cluster head
hop_counts_initial = np.zeros(num_le, dtype=int)
for i in range(num_le):
    le_node_index = num_ch + i  # Adjust index for all_positions array (after cluster heads)
    assigned_ch_index = le_assignments_initial[i]
    hop_counts_initial[i] = calculate_hop_count(le_node_index, assigned_ch_index, adjacency_matrix)

# -------------------------------
# Part 2: Applying Tabu Metaheuristic for Optimization
# -------------------------------

# Initialize the best solution setup with the initial assignments and hop counts
best_assignments = le_assignments_initial.copy()
best_hop_counts = hop_counts_initial.copy()
best_total_hops = hop_counts_initial.sum()
best_clusters = clusters_initial.copy()

# Build KDTree for cluster heads (used for efficient nearest neighbor queries)
kdtree_ch = KDTree(ch_positions)

# Tabu Search Parameters
tabu_list = []  # List to keep track of recent moves (to avoid cycling back)
max_tabu_size = 100  # Maximum size of the tabu list
num_iterations = 200  # Number of iterations for the tabu search
threshold = 0  # Threshold for accepting moves (only accept moves that do not increase hop count)
k_nearest = 3  # Number of nearest cluster heads to consider for reassignment

# Function to calculate the closest cluster head to a given low-end node
def calculate_distance_to_closest_cluster_head(node_index, ch_positions, le_positions):
    node_position = le_positions[node_index]
    # Calculate distances from the node to all cluster heads
    distances = np.linalg.norm(ch_positions - node_position, axis=1)
    closest_ch_index = np.argmin(distances)  # Index of the closest cluster head
    return closest_ch_index, distances[closest_ch_index]

# Enhancing the tabu search with proximity check
for iteration in range(num_iterations):
    improved = False  # Flag to check if any improvement is made in this iteration

    # Shuffle nodes to consider them in random order for diversification
    nodes = list(range(num_le))
    random.shuffle(nodes)

    # Single Move: Reassign nodes to the nearest cluster head based on distance
    for node in nodes:
        le_node_index = num_ch + node  # Adjust index for all_positions
        current_ch = best_assignments[node]
        current_hop_count = best_hop_counts[node]

        # Calculate the closest cluster head based on distance
        closest_ch_index, distance_to_closest_ch = calculate_distance_to_closest_cluster_head(node, ch_positions, le_positions)

        # If the closest cluster head is different from the current one, consider reassignment
        if closest_ch_index != current_ch:
            move = (node, current_ch, closest_ch_index)  # Define the move as a tuple
            if move in tabu_list:
                continue  # Skip moves that are in the Tabu list to avoid cycling

            # Tentatively reassign node to the closest cluster head
            tentative_assignments = best_assignments.copy()
            tentative_assignments[node] = closest_ch_index

            # Calculate new hop count after reassignment
            new_hop_count = calculate_hop_count(le_node_index, closest_ch_index, adjacency_matrix)

            # If the hop count improves or stays the same, accept the move
            if new_hop_count <= current_hop_count:
                best_assignments = tentative_assignments  # Update best assignments
                best_hop_counts[node] = new_hop_count  # Update hop counts
                best_total_hops = best_hop_counts.sum()  # Update total hop counts
                # Update Tabu list
                tabu_list.append(move)
                if len(tabu_list) > max_tabu_size:
                    tabu_list.pop(0)  # Maintain the tabu list size
                improved = True  # Mark that an improvement was made

    # The pairwise and cyclic exchanges can be implemented here for further optimization
    # For simplicity, they are omitted in this code, but they can be added following a similar pattern
    # Stop if no improvement was made in this iteration
    if not improved:
        break  # Exit the loop if no better solution is found

# -------------------------------
# Final Results
# -------------------------------

# Recalculate Hop Counts After Optimization
for i in range(num_le):
    le_node_index = num_ch + i  # Adjust index for all_positions
    assigned_ch_index = best_assignments[i]  # Get the assigned cluster head index
    best_hop_counts[i] = calculate_hop_count(le_node_index, assigned_ch_index, adjacency_matrix)

# Output the Results
initial_total_hops = hop_counts_initial.sum()
optimized_total_hops = best_hop_counts.sum()

print(f"Total Hop Counts Before Optimization: {initial_total_hops}")
print(f"Total Hop Counts After Optimization: {optimized_total_hops}")

# -------------------------------
# Visualization: Before and After Optimization
# -------------------------------

# Create a figure with two subplots side by side for comparison
fig, axes = plt.subplots(1, 2, figsize=(20, 10))

# ---------------------------
# Plot Initial Clustering
# ---------------------------
ax1 = axes[0]
# Plot Voronoi boundaries based on initial cluster head positions
voronoi_plot_2d(vor, ax=ax1, show_vertices=False, line_colors='orange', line_width=2, show_points=False)

# Plot Cluster Heads as red triangles
ax1.scatter(ch_positions[:, 0], ch_positions[:, 1], c='red', label='Cluster Heads', marker='^', s=100)
# Plot Low-End Nodes as blue circles
ax1.scatter(le_positions[:, 0], le_positions[:, 1], c='blue', label='Low-End Nodes', s=50)

# Connect each low-end node to its assigned cluster head with dashed gray lines
for i in range(num_le):
    ax1.plot([le_positions[i, 0], ch_positions[le_assignments_initial[i], 0]], 
             [le_positions[i, 1], ch_positions[le_assignments_initial[i], 1]], 
             color='gray', linestyle='--', linewidth=0.5)

# Set plot title and labels
ax1.set_title('Initial Random Clustering with Voronoi Diagram')
ax1.set_xlabel('X Coordinate')
ax1.set_ylabel('Y Coordinate')
ax1.set_xlim(0, area_size)
ax1.set_ylim(0, area_size)
ax1.legend()
ax1.grid(True)

# ---------------------------
# Plot Optimized Clustering
# ---------------------------
ax2 = axes[1]
# Plot Voronoi boundaries based on initial cluster head positions (same as before)
voronoi_plot_2d(vor, ax=ax2, show_vertices=False, line_colors='orange', line_width=2, show_points=False)

# Plot Cluster Heads without colored outlines
ax2.scatter(ch_positions[:, 0], ch_positions[:, 1], c='red', label='Cluster Heads', marker='^', s=100)

# Define colors for clusters (cycling through the list if more clusters than colors)
colors = ['blue', 'green', 'purple', 'cyan', 'magenta', 'yellow', 'orange', 'brown', 'pink', 'gray']

# Plot Low-End Nodes with optimized assignments, coloring by cluster
for i in range(num_le):
    assignment = best_assignments[i]  # Get the assigned cluster head index
    color = colors[assignment % len(colors)]  # Select color based on cluster head index
    ax2.scatter(le_positions[i, 0], le_positions[i, 1], c=color, marker='o', s=50, alpha=0.6)

    # Connect each low-end node to its assigned cluster head with dashed gray lines
    ax2.plot([le_positions[i, 0], ch_positions[assignment, 0]],
             [le_positions[i, 1], ch_positions[assignment, 1]],
             color='gray', linestyle='--', linewidth=0.5)

# Set plot title and labels
ax2.set_title('Optimized Clustering After Tabu Search with Voronoi Diagram')
ax2.set_xlabel('X Coordinate')
ax2.set_ylabel('Y Coordinate')
ax2.set_xlim(0, area_size)
ax2.set_ylim(0, area_size)
ax2.legend()
ax2.grid(True)

# Adjust layout and save the figure to a file
plt.tight_layout()
plt.savefig('voronoi_optimization_updated.png', dpi=300)
plt.show()
