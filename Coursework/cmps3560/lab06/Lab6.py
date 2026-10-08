#%% Define fuzzy sets
bottle = ((0.0, 0.2), (0.5, 0.5), (1.0, 1.0), (0.5, 1.5), (0.0, 2.0))
short = ((1.0, 0.1), (0.75, 0.5), (0.5, 1.0), (0.25, 1.5), (0.0, 2.0))
moderate = ((1.0, 50), (0.5, 80), (0.0, 120))
hot = ((0.0, 50), (0.5, 80), (1.0, 120))

#%% Membership function
def membership(inputValue, fuzzySet):
    closest_value = None
    min_diff = float('inf')
    
    for fuzzyValue, crisp in fuzzySet:
        if crisp == inputValue:
            return fuzzyValue
        diff = abs(crisp - inputValue)
        if diff < min_diff:
            min_diff = diff
            closest_value = fuzzyValue
    
    return closest_value

#%% Test membership function
print(membership(-3, bottle))  # Expected: 0.0
print(membership(1.0, bottle))  # Expected: 1.0
print(membership(0.3, bottle))  # Expected: 0.0
print(membership(0.712321345, bottle))  # Expected: 0.5
print(membership(10000, bottle))  # Expected: 0.0 

#%% Inverse Membership function
def inverseMembership(fuzzyValue, fuzzySet):
    closest_crisp = None
    min_diff = float('inf')
    
    for fVal, crisp in fuzzySet:
        diff = abs(fVal - fuzzyValue)
        if diff < min_diff:
            min_diff = diff
            closest_crisp = crisp
    
    return closest_crisp

#%% Test inverse membership function
print(inverseMembership(0.0, bottle))  # Expected: 0.2
print(inverseMembership(0.2, bottle))  # Expected: 0.2
print(inverseMembership(0.5, bottle))  # Expected: 0.5
print(inverseMembership(0.8, bottle))  # Expected: 1.0
print(inverseMembership(1.0, bottle))  # Expected: 1.0

#%% Monotonic Inference
km = 3
temp = 80
fuzzyDistance = membership(km, short)
fuzzyTemp = membership(temp, hot)
premiseFuzzy = max(fuzzyDistance, fuzzyTemp)
crispOutput = inverseMembership(premiseFuzzy, bottle)

print(f"The user walked {km} km and it is {temp}F. Fuzzy system recommends: {crispOutput} bottles of water.")
