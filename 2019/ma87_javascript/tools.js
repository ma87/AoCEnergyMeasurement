const path = require("path");
const { readFileSync } = require("fs");

/*const input = readFileSync(path.resolve(__dirname, "./input.txt"), "utf8")
  .trim()
  .split("\n")
  .map(n => parseInt(n));*/
exports.parseInput = function(fileInput, parserFunc, outputParser)
{
	return readFileSync(path.resolve(__dirname, fileInput), "utf8")
  .trim()
  .split("\n")
  .map(parserFunc);
}
