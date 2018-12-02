#!/usr/bin/env python3


def get_common_letters(word1, word2):
    similar_part = [x for x, y in zip(word1, word2) if x == y]
    word1_length = len(word1)
    if word1_length == len(word2) and len(similar_part) == word1_length - 1:
        return ''.join(similar_part)
    return None


def find_similar_words(words):
    res = []
    for idx, current_word in enumerate(words):
        for word in words[idx+1:]:
            similar_word = get_common_letters(current_word, word)
            if similar_word:
                res.append(similar_word)
                continue
    return res


if __name__ == "__main__":
    with open('data', 'r') as infile:
        words = [line.strip('\n') for line in infile]
        print(find_similar_words(words))
