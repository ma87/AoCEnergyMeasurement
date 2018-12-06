use std::fs::File;
use std::io::prelude::*;

// match is a reserved keyword
fn charmatch(x: char, y: char) -> bool {
    let lx = x.to_lowercase().last();
    let ly = y.to_lowercase().last();
    return lx == ly && x != y;
}

fn final_reduce(mut part1: String, mut part2: String) -> String {
    if part1.is_empty() {
        return part2;
    } else if part2.is_empty() {
        return part1;
    } else if charmatch(part1.chars().last().unwrap(), part2.chars().nth(0).unwrap()) {
        part1.pop();
        part2.remove(0);
        return final_reduce(part1, part2);
    } else {
        let mut rv = String::new();
        rv.push_str(&part1);
        rv.push_str(&part2);
        return rv;
    }
}
    

fn reduce(seq: String) -> String {
    let l = seq.len();
    if l < 2 {
        return seq;
    } else if l == 2 {
        if charmatch(seq.chars().nth(0).unwrap(), seq.chars().last().unwrap()) {
            return String::new();
        } else {
            return seq;
        }
    } else {
        let (part1, part2) = seq.split_at(l/2);
        let mut rv1 = reduce(part1.to_string());
        let rv2 = reduce(part2.to_string());
        if part1 == rv1 && part2 == rv2 {
            return final_reduce(rv1, rv2);
        } else {
            rv1.push_str(&rv2);
            return reduce(rv1);
        }
    }
}

fn main() {
    let filename = "input";

    let mut f = File::open(filename).expect("file not found");

    let mut content = String::new();
    f.read_to_string(&mut content)
        .expect("something went wrong reading the file");

    content.pop();  // remove newline char

    let mut minlen = content.len();
    let step1 = reduce(content);
    for letter in "azertyuiopsdfghjklmwxcvbn".chars() {
        let mut tmp: String = step1.replace(letter, "");
        let upper = letter.to_uppercase().last().unwrap();
        tmp = tmp.replace(upper, "");
        tmp = reduce(tmp);
        if tmp.len() < minlen {
            minlen = tmp.len();
            println!("removed: {}", letter);
        }
    }


    println!("{}", minlen);
}
