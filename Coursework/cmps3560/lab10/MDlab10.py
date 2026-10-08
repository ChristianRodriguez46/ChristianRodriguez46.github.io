# %% [markdown]
# # Lab 10-1 – Genetic Algorithm “Max-Ones” Solver
# **CMPS 3560** • background-section implementation  
# This notebook mirrors the plain-Python script I just sent, but chunked into
# easy-to-run cells and peppered with short explanations.

# 1. Imports & Hyper-parameters

import random
from typing import List, Tuple

# Population & GA settings (taken directly from the lab sheet)
N_POP            = 25          # population size 𝑁
CHROM_LEN        = 32          # bits per chromosome
TOURNAMENT_K     = 3           # selection subset size
P_CROSSOVER      = 1.0         # crossover probability 𝑝𝑐
P_MUTATION       = 0.01        # bit-flip probability 𝑝𝑚
MAX_GENERATIONS  = 10_000      # hard safety stop

# %% [markdown]
# 2. Helper type aliases

Chromosome = List[int]                 # a list of 0/1 ints
Individual = Tuple[Chromosome, int]    # (genes, fitness)

# %% [markdown]

# 3. Core GA utility functions

def random_chromosome() -> Chromosome:
    """Create a brand-new random chromosome."""
    return [random.randint(0, 1) for _ in range(CHROM_LEN)]

def fitness(chrom: Chromosome) -> int:
    """Fitness = number of ones."""
    return sum(chrom)

def tournament_selection(pop: List[Individual]) -> Chromosome:
    """Pick the fittest out of *k* randomly sampled individuals."""
    subset = random.sample(pop, TOURNAMENT_K)
    winner, _ = max(subset, key=lambda ind: ind[1])
    return winner[:]          # return a copy

def one_point_crossover(p1: Chromosome, p2: Chromosome
                        ) -> Tuple[Chromosome, Chromosome]:
    """Swap tails at a random cut‐point."""
    cut = random.randint(1, CHROM_LEN - 1)
    return (p1[:cut] + p2[cut:], p2[:cut] + p1[cut:])

def mutate(chrom: Chromosome) -> None:
    """Flip one randomly chosen bit with probability *P_MUTATION*."""
    if random.random() < P_MUTATION:
        idx = random.randrange(CHROM_LEN)
        chrom[idx] = 1 - chrom[idx]

# %% [markdown]
# 4. Main GA loop

def genetic_algorithm() -> Tuple[Chromosome, int, int]:
    """Run until an all-ones chromosome appears or the generation cap is hit."""
    # --- 4.1 initial population ---
    population: List[Individual] = [
        (random_chromosome(), 0) for _ in range(N_POP)
    ]
    population = [(c, fitness(c)) for (c, _) in population]

    # --- 4.2 evolution loop ---
    for gen in range(1, MAX_GENERATIONS + 1):
        best_chrom, best_fit = max(population, key=lambda ind: ind[1])
        if best_fit == CHROM_LEN:                 # solution found!
            print(f"✔ Found optimum in gen {gen-1}")
            return best_chrom, best_fit, gen-1

        new_pop: List[Individual] = []
        while len(new_pop) < N_POP:
            if random.random() <= P_CROSSOVER:
                pa = tournament_selection(population)
                pb = tournament_selection(population)
                while pb == pa:                   # avoid duplicate parent
                    pb = tournament_selection(population)
                child1, child2 = one_point_crossover(pa, pb)
            else:
                child1 = tournament_selection(population)
                child2 = tournament_selection(population)

            mutate(child1)
            mutate(child2)
            new_pop.append((child1, fitness(child1)))
            if len(new_pop) < N_POP:
                new_pop.append((child2, fitness(child2)))

        population = new_pop                      # step 5: next generation
        if gen % 50 == 0:
            print(f"Gen {gen}: best fitness so far = {best_fit}")

    # failsafe return
    best_chrom, best_fit = max(population, key=lambda ind: ind[1])
    return best_chrom, best_fit, MAX_GENERATIONS

# %%
solution, fit, gens = genetic_algorithm()
print('-'*40)
print("Best chromosome :", "".join(map(str, solution)))
print("Fitness achieved:", fit)
print("Generations run :", gens)