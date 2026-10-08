from collections import deque
def pl_fc_entails(KB, q):
    """
    Implements the forward chaining algorithm for propositional logic.
    
    Parameters:
        KB: List of tuples representing the knowledge base.
            Each tuple contains (list of premises, conclusion).
        q: The query proposition to check entailment.

    Returns:
        True if KB entails q, otherwise False.
    """
    

    # Count table: Number of premises left to be satisfied for each rule
    count = {c: len(premise) for premise, c in KB}
    # count = [3,1,2]
    
    # Inferred table: Track if a proposition has been inferred
    inferred = {symbol: False for premise, c in KB for symbol in premise + [c]}
    # inferred = []
    
    # Agenda: Queue of known true symbols
    agenda = deque(symbol for premise, _ in KB for symbol in premise)
    # agenda = ["barks","hoots","looks","swims","quacks"]
    
    # Forward chaining process
    while agenda:
        p = agenda.pop()  # Pop the first symbol from agenda

        if p == q:
            print( "Goal is entailed!" )
            return True  # Query is entailed

        if not inferred[p]:  # Mark symbol as inferred if not already done
            inferred[p] = True

            for premise, conclusion in KB:
                if p in premise:
                    count[conclusion] -= 1  # Reduce count of unsatisfied premises
                    if count[conclusion] == 0:  # If all premises satisfied
                        agenda.append(conclusion)  # Add conclusion to agenda

    return False  # Query is not entailed

# Example Knowledge Base
KB = [
    (["looks", "swims", "quacks"], "duck"),
    (["barks"], "dog"),
    (["hoots", "flies"], "owl")
]

# Query to check entailment
q = "duck"

# Run the forward chaining algorithm
result = pl_fc_entails(KB, q)
print(f"Is '{q}' entailed by KB? {result}")
