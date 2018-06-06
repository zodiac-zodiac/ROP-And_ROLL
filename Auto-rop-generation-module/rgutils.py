
def deleteDuplicateGadgets(currentGadgets):
    gadgets_content_set = set()
    unique_gadgets = []
    for gadget in currentGadgets:
        gad = gadget["gadget"]
        if gad in gadgets_content_set:
            continue
        gadgets_content_set.add(gad)
        unique_gadgets += [gadget]
    return unique_gadgets

def alphaSortgadgets(currentGadgets):
    return sorted(currentGadgets, key=lambda key : key["gadget"]) 

