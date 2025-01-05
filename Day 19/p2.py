from typing import List

content = [line.rstrip() for line in open("input.txt")]

towels: List = content[0].split(", ")
towelsDict = {towel: True for towel in towels}
maxLen = max([len(towel) for towel in towels])
hashmap = {}


def patternExists(pattern: str):
    if len(pattern) == 0:
        return True
    if pattern in hashmap:
        return hashmap[pattern]

    count = 0

    for i in reversed(range(1, min(len(pattern) + 1, maxLen + 1))):
        if pattern[:i] in towelsDict:
            count += patternExists(pattern[i:])

    hashmap[pattern] = count
    return count


countSum = 0
for line in content[2:]:
    patternExists(line)
    countSum += hashmap[line]

print(countSum)
