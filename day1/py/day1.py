with open("inputs/day1-1.txt", "r") as f:

    l1 = []
    l2 = []

    for line in f.readlines():
        tokens = line.split()
        l1.append(int(tokens[0]))
        l2.append(int(tokens[1]))

    result = 0
    for n1, n2 in zip(sorted(l1), sorted(l2)):
        result += abs(n1 - n2)

    print(result)

with open("inputs/day1-1.txt", "r") as f:

    l1 = []
    l2 = []

    for line in f.readlines():
        tokens = line.split()
        l1.append(int(tokens[0]))
        l2.append(int(tokens[1]))

    from collections import Counter

    c = Counter(l2)

    result = 0
    for n1 in l1:
        result += n1 * c.get(n1, 0)

    print(result)
