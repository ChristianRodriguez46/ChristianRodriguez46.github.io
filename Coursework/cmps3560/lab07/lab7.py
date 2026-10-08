# Define fuzzy sets
bottle = ((0.0, 0.2), (0.5, 0.5), (1.0, 1.0), (0.5, 1.5), (0.0, 2.0))
short = ((1.0, 0.1), (0.75, 0.5), (0.5, 1.0), (0.25, 1.5), (0.0, 2.0))
moderate = ((1.0, 50), (0.5, 80), (0.0, 120))
hot = ((0.0, 50), (0.5, 80), (1.0, 120))

# Membership function
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

# Test membership function
print(membership(-3, bottle))          # Expected: 0.0
print(membership(1.0, bottle))         # Expected: 1.0
print(membership(0.3, bottle))         # Expected: 0.0
print(membership(0.712321345, bottle)) # Expected: 0.5
print(membership(10000, bottle))       # Expected: 0.0 

# Inverse Membership function
def inverseMembership(fuzzyValue, fuzzySet):
    closest_crisp = None
    min_diff = float('inf')
    
    for fVal, crisp in fuzzySet:
        diff = abs(fVal - fuzzyValue)
        if diff < min_diff:
            min_diff = diff
            closest_crisp = crisp
    
    return closest_crisp

# Test inverse membership function
print(inverseMembership(0.0, bottle))  # Expected: 0.2
print(inverseMembership(0.2, bottle))  # Expected: 0.2
print(inverseMembership(0.5, bottle))  # Expected: 0.5
print(inverseMembership(0.8, bottle))  # Expected: 1.0
print(inverseMembership(1.0, bottle))  # Expected: 1.0

# Monotonic Inference
km = 3
temp = 80
fuzzyDistance = membership(km, short)
fuzzyTemp = membership(temp, hot)
premiseFuzzy = max(fuzzyDistance, fuzzyTemp)
crispOutput = inverseMembership(premiseFuzzy, bottle)

print(f"The user walked {km} km and it is {temp}F. Fuzzy system recommends: {crispOutput} bottles of water.")

# Mamdani Inference
def mamdani_inference(L, T):
    # Rule 1: IF distance is short THEN water is none
    rule1ant = membership(L, short)

    # Rule 2: IF distance is medium AND temperature is moderate THEN water is bottle
    rule2ant = min(membership(L, medium), membership(T, moderate))

    # Rule 3: IF distance is long OR temperature is hot THEN water is alot
    rule3ant = max(membership(L, long), membership(T, hot))

    numerator = 0
    denominator = 0

    # Mamdani aggregation via numerical integration from 0 to 2 (step 0.1)
    for x in [i * 0.1 for i in range(21)]:
        u1 = rule1ant * membership(x, none)
        u2 = rule2ant * membership(x, bottle)
        u3 = rule3ant * membership(x, alot)
        u = max(u1, u2, u3)  # max for union (aggregation)
        numerator += u * x
        denominator += u

    if denominator == 0:
        return 0.0  # Prevent division by zero

    return numerator / denominator

# Define full fuzzy sets from Appendix A
none = ((1.0,0), (0.75,0.1), (0.50,0.2), (0.25,0.3), (0.0,0.4))
bottle = ((0.0,0.2), (0.5,0.5), (1.0,1.0), (0.5,1.5), (0.0,2.0))
alot = ((0.0,1.0), (0.25,1.25), (0.5,1.5), (0.75,1.75), (1.0,2.0))

moderate = ((1.0,48), (0.66,52), (0.33,68), (0.0,72), (0.33,78), (0.66,84), (1.0,92))
hot = ((0.0,72), (0.3,78), (0.6,84), (0.9,92), (1.0,104))

short = ((1.0,0.1), (0.66,0.5), (0.33,1.0), (0.0,5.0), (0.0,10.0), (0.0,50.0))
medium = ((0.0,0.1), (0.33,0.5), (1.0,1.0), (0.66,5.0), (0.33,10.0), (0.0,50.0))
long = ((0.0,0.1), (0.0,0.5), (0.61,1.0), (0.95,5.0), (0.99,10.0), (1.0,50.0))

# Test Mamdani Inference
T = 80  # temperature
L = 2   # distance
output = mamdani_inference(L, T)
print(f"Mamdani Inference: Distance = {L}km, Temp = {T}F => Recommended water: {round(output, 2)}L")
