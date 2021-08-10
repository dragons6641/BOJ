import sys;

# sys.stdin = open("input1.txt", 'r');

(N, M) = map(int, input().split());

(pokemonList, pokemonDict) = ([''], dict());

for pokemonIdx in range(1, N + 1):
    pokemonName = input();
    pokemonList.append(pokemonName);
    pokemonDict[pokemonName] = pokemonIdx;

for queryIdx in range(1, M + 1):
    queryStr = input();
    print(pokemonList[int(queryStr)] if (queryStr.isdigit()) else pokemonDict[queryStr]);
