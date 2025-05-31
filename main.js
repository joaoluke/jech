const fs = require('fs');

// Simula armazenamento de variáveis
const variables = {};

// Remove aspas de uma string
function removeQuotes(str) {
  return str.replace(/^"(.*)"$/, '$1');
}

// Interpreta uma linha de código
function interpretLine(line) {
  line = line.trim();

  if (line.startsWith("keep")) {
    const match = line.match(/keep\s+(\w+)\s*=\s*(.*);/);
    if (match) {
      const name = match[1];
      let value = match[2].trim();
      value = removeQuotes(value);
      variables[name] = value;
    }
  } else if (line.startsWith("say")) {
    const match = line.match(/say\((.*)\);/);
    if (match) {
      let arg = match[1].trim();
      arg = removeQuotes(arg);
      const val = variables[arg] || arg;
      console.log(val);
    }
  }
}

// Lê o arquivo .jc e interpreta linha por linha
function run(filePath) {
  const content = fs.readFileSync(filePath, 'utf-8');
  const lines = content.split('\n');
  for (const line of lines) {
    interpretLine(line);
  }
}

// Argumento da linha de comando
const file = process.argv[2];
if (!file) {
  console.log("Usage: node main.js <file.jc>");
  process.exit(1);
}

run(file);
