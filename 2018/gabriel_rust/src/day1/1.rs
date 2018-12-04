use std::io::BufReader;
use std::io::BufRead;
use std::fs::File;
use std::path::Path;
                
fn main() {   
	let mut freq: i32 = 0;

	let path = Path::new("input");
	let mut file = File::open(&path).expect("Unable to open");
    let mut reader = BufReader::new(&file);

    for line in reader.lines() {
        let l = line.unwrap();
		let f: i32 = l.parse().unwrap();
		freq += f;
    }           

	println!("{}", freq);
}
