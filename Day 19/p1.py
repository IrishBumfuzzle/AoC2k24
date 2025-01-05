from typing import List

content = [line.rstrip() for line in open("input.txt")]

towels: List = content[0].split(", ")
towelsDict = {towel: True for towel in towels}
maxLen = max([len(towel) for towel in towels])
hashmap = {}


def patternExists(pattern: str) -> bool:
    if len(pattern) == 0:
        return True
    if pattern in hashmap:
        return hashmap[pattern]
    for i in reversed(range(1, maxLen + 1)):
        if pattern[:i] in towelsDict:
            hashmap[pattern[i:]] = patternExists(pattern[i:])
            if patternExists(pattern[i:]):
                return True
    hashmap[pattern[i:]] = False
    return False


count = 0
for line in content[2:]:
    if patternExists(line):
        count += 1

print(count)
