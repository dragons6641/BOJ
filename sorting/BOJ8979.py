max_nation = 1000;
rank = 1;

nation_list = [];
gold_list = []
silver_list = []
bronze_list = []

tmp = input().split();
n, k = int(tmp[0]), int(tmp[1]);

# print(n, k);

for i in range(n):
    tmp = input().split();

    nation, gold, silver, bronze = int(tmp[0]), int(tmp[1]), int(tmp[2]), int(tmp[3]);

    nation_list.append(nation);
    gold_list.append(gold);
    silver_list.append(silver);
    bronze_list.append(bronze);

    if (nation == k):
        index = i;

"""
print(nation_list);
print(gold_list);
print(silver_list);
print(bronze_list);
"""

# print(index);

for i in range(n):
    if (gold_list[index] < gold_list[i]):
        """
        print('gold');
        print(index, i);
        """

        rank += 1;
    elif (gold_list[index] > gold_list[i]):
        continue;
    else:
        if (silver_list[index] < silver_list[i]):
            """
            print('silver');
            print(index, i);
            """
            rank += 1;
        elif (silver_list[index] > silver_list[i]):
            continue;
        else:
            if (bronze_list[index] < bronze_list[i]):
                """
                print('bronze');
                print(index, i);
                """

                rank += 1;
            else:
                continue;

print(rank);
