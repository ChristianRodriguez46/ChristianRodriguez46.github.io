# python3 lab10.py
"""
Genetic Algorithm - Max-Ones Problem
CMPS 3560 • Lab 10-1 implementation
Author: Christian Rodriguez
"""

import random
from typing import List, Tuple

# ---------- 1. Hyper-parameters (from the lab sheet) ----------
N_POP            = 25          # population size 𝑁
CHROM_LEN        = 32          # chromosome length (bits)
TOURNAMENT_K     = 3           # tournament subset size k  (k « N)
P_CROSSOVER      = 1.0         # probability parent will mate (𝑝𝑐)
P_MUTATION       = 0.01        # probability a *single* bit flips in an offspring (𝑝𝑚)
MAX_GENERATIONS  = 10_000      # emergency cap – should converge long before this


# ---------- 2. Data types ----------
# A chromosome is a list[int] of 0/1s; we wrap it with its fitness in a tuple.
Chromosome   = List[int]
Individual   = Tuple[Chromosome, int]   # (genes, fitness)


# ---------- 3. Core helper functions ----------
def random_chromosome() -> Chromosome:
    """Generate a brand-new, random chromosome"""
    return [random.randint(0, 1) for _ in range(CHROM_LEN)]


def fitness(chrom: Chromosome) -> int:
    """Number of ones = fitness value (higher is better)"""
    return sum(chrom)


def tournament_selection(pop: List[Individual]) -> Chromosome:
    """
    Pick the *best* chromosome from a randomly chosen subset of size k.
    No self-selection issues here because we always call this on the *full* pop.
    """
    subset = random.sample(pop, TOURNAMENT_K)
    # max() chooses the tuple whose second element (fitness) is largest
    winner, _ = max(subset, key=lambda ind: ind[1])
    return winner[:]  # copy to break references


def one_point_crossover(parent1: Chromosome, parent2: Chromosome
                        ) -> Tuple[Chromosome, Chromosome]:
    """
    Classical one-point crossover.
    • Choose a cut point in (1 … CHROM_LEN-1)
    • Swap the tails to create two offspring
    """
    cut = random.randint(1, CHROM_LEN - 1)
    child1 = parent1[:cut] + parent2[cut:]
    child2 = parent2[:cut] + parent1[cut:]
    return child1, child2


def mutate(chrom: Chromosome) -> None:
    """With probability P_MUTATION flip ONE random bit *in place*"""
    if random.random() < P_MUTATION:
        idx           = random.randrange(CHROM_LEN)
        chrom[idx]    = 1 - chrom[idx]  # flip 0 ↔ 1


# ---------- 4. GA main loop ----------
def genetic_algorithm() -> Tuple[Chromosome, int, int]:
    """
    Run until we discover an all-ones chromosome or hit MAX_GENERATIONS.
    Returns (best_chromosome, best_fitness, generations_run)
    """
    # -- 4.1 initial random population --
    population: List[Individual] = [
        (random_chromosome(), 0) for _ in range(N_POP)
    ]

    # compute initial fitnesses
    population = [(c, fitness(c)) for (c, _) in population]

    # -- 4.2 generation loop --
    for gen in range(1, MAX_GENERATIONS + 1):

        # ----- termination test -----
        best_chrom, best_fit = max(population, key=lambda ind: ind[1])
        if best_fit == CHROM_LEN:
            print(f"✔ Solution found in generation {gen-1}")
            return best_chrom, best_fit, gen-1

        # ----- mating + mutation phase (step 4 in lab) -----
        new_pop: List[Individual] = []

        while len(new_pop) < N_POP:
            # --- selection ---
            if random.random() <= P_CROSSOVER:
                # Pick two parents via tournament
                parent_a = tournament_selection(population)
                parent_b = tournament_selection(population)
                # Ensure distinct parents (rare edge case)
                while parent_b == parent_a:
                    parent_b = tournament_selection(population)

                # --- crossover (two offspring) ---
                child1, child2 = one_point_crossover(parent_a, parent_b)
            else:
                # No crossover; just clone two random parents
                child1 = tournament_selection(population)
                child2 = tournament_selection(population)

            # --- mutation ---
            mutate(child1)
            mutate(child2)

            # --- add offspring & compute their fitness immediately ---
            new_pop.append((child1, fitness(child1)))
            if len(new_pop) < N_POP:               # keep population size exact
                new_pop.append((child2, fitness(child2)))

        # ----- move to next generation (step 5) -----
        population = new_pop

        print("*" * 50)
        for i, (chrom, fit) in enumerate(population, 1):
            print(f"Individual {i:2d}: [{''.join(map(str, chrom))}] and fitness is {fit}")
        print("*" * 50)
        print(f"Generation {gen}: Best individual’s fitness is {best_fit}, "
            f"continuing with next generation!")
        print("*" * 50)

        # optional: status printout every 50 generations
        # if gen % 50 == 0:
        #     print(f"Gen {gen}: current best fitness = {best_fit}")

    # failsafe: return best encountered
    best_chrom, best_fit = max(population, key=lambda ind: ind[1])
    return best_chrom, best_fit, MAX_GENERATIONS


# ---------- 5. Driver ----------
if __name__ == "__main__":
    solution, fitness_val, generations = genetic_algorithm()
    print("-"*40)
    print("Best chromosome :", "".join(map(str, solution)))
    print("Fitness achieved:", fitness_val)
    print("Generations run :", generations)
