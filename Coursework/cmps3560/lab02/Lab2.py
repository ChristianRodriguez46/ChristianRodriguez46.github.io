# Define the inital database (DB) of known facts
DB = ["looks", "swims", "quacks"] # Given facts

# Define the knowledge base (KB) of rules
KB = [
    (["looks", "swims", "quacks"], "duck"), # If it looks, swims, and quacks, it's a duck
    (["barks"], "dog"),  # If it barks, it's a dog
    (["hoots", "flies"], "owl") # If it hoots and flies, it's an owl
]

count = 1     # Track the number of iterations
changes = True  # Flag to check if new knowledge is added

# Forward Chaing algorithm

while changes:
    changes = False     # Set the flag that there have been no changes to false
    print(f"Starting iteration {count}")

    for rule in KB:     # Iterate through each rule in KB
        antecedent, consequent = rule    # Extract the premise (conditions) and conclusion

        print("Considering rule:")
        print(f"If {antecedent} then {consequent}")

        # Check if all conditions in antecedent are in DB
        satisfied = all (fact in DB for fact in antecedent)

        if satisfied and consequent not in DB:
            DB.append(consequent)
            changes = True
            print("Antecedent is satisfied, implying:", consequent)
            print("Updated DB:", DB)
        elif satisfied and consequent in DB:
            print("Consequent already in DB. no change.")
        else:
            print("Antecedent not satisfied, rule does not fire.")
    
    count += 1
    print("\n")

print("No more changes. Final DB:", DB)