import sys

if len(sys.argv) <= 1:
    exit(1)

filename = sys.argv[1]

def get_max_coords(claims):
    max_x = 0
    max_y = 0
    for claim in claims:
        if (claim.x + claim.width) > max_x:
            max_x = claim.x + claim.width
        if (claim.y + claim.height) > max_y:
            max_y = claim.y + claim.height
    return (max_x, max_y)

def fill_fabric(fabric, claims):
    for claim in claims:
        for i in range(claim.x, claim.x + claim.width, 1):
            for j in range(claim.y, claim.y + claim.height, 1):
                fabric[j][i].append(claim.id)

def get_id(fabric, i, j):
    if len(fabric[j][i]) == 1:
        return str(fabric[j][i][0])
    elif len(fabric[j][i]) > 1:
        return "X"
    else:
        return "."

def get_number_overlap_inches(fabric):
    counter = 0

    for j in range(len(fabric)):
        for i in range(len(fabric[j])):
            if len(fabric[j][i]) > 1:
                counter += 1

    return counter

def get_id_with_no_overlap(fabric, claims):
    overlap_ids = {0}

    for j in range(len(fabric)):
        for i in range(len(fabric[j])):
            if len(fabric[j][i]) > 1:
                for overlap_id in fabric[j][i]:
                    overlap_ids.add(overlap_id)

    for claim in claims:
        if claim.id not in overlap_ids:
            return claim.id
    return -1

def print_fabric(fabric):
    for j in range(len(fabric)):
        print("".join([get_id(fabric, i, j) for i in range(len(fabric[j]))]))

class Claim():
    def __init__(self, id, x, y, width, height):
        self.id = id
        self.x = x
        self.y = y
        self.height = height
        self.width = width

with open(filename, 'r') as f:
    claims_data = f.readlines()
    claims = []
    for claim_data in claims_data:
        data = claim_data.split(' ')
        if len(data) != 4:
            print('error in parsing data, len = ' + str(len(data))) 
            for word in data:
                print('word = ' + word)
            exit(1)

        id = int(data[0][1:])
        #print('id = ' + str(id))
        x, y = data[2].split(":")[0].split(",")
        width, height = data[3].split("x")
        claims.append(Claim(id, int(x), int(y), int(width), int(height)))

    max_x, max_y = get_max_coords(claims)
    fabric = [[[] for i in range(max_x + 1)] for j in range(max_y + 1)]
    fill_fabric(fabric, claims)

print('solution 1 = ' + str(get_number_overlap_inches(fabric)))
print('solution 2 = ' + str(get_id_with_no_overlap(fabric, claims)))
