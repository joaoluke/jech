# 📚 JECH Examples

This directory contains example programs demonstrating JECH language features.

## 🎯 Getting Started

Run any example with:
```bash
./build/jech examples/01_hello_world.jc
```

## 📂 Examples Overview

### Basics
| File | Description |
|------|-------------|
| `01_hello_world.jc` | Your first JECH program |
| `02_say_types.jc` | Printing strings, numbers, booleans |
| `03_variables.jc` | Declaring variables with `keep` |
| `04_reassignment.jc` | Changing variable values |

### Conditionals
| File | Description |
|------|-------------|
| `05_when_boolean.jc` | `when` with true/false conditions |
| `06_when_comparison.jc` | `when` with `>`, `<`, `==` operators |
| `07_when_else.jc` | `when`/`else` for branching logic |

### Arithmetic
| File | Description |
|------|-------------|
| `08_arithmetic.jc` | Addition, subtraction, multiplication, division |

### Practical Examples
| File | Description |
|------|-------------|
| `09_practical_user_auth.jc` | Simulating a login system |
| `10_practical_inventory.jc` | Managing stock levels |
| `11_practical_game_score.jc` | Game score tracking |
| `12_practical_temperature.jc` | Temperature monitoring |
| `13_practical_banking.jc` | Bank account operations |
| `14_practical_quiz.jc` | Quiz with scoring |
| `15_practical_todo.jc` | Todo list management |

### Advanced
| File | Description |
|------|-------------|
| `16_edge_cases.jc` | Boundary conditions and special cases |

## 🧪 Running All Examples

```bash
# Run each example
for file in examples/*.jc; do
    echo "=== Running $file ==="
    ./build/jech "$file"
    echo ""
done
```

## 📝 Legacy Examples

The following files contain older examples that are still valid:
- `say_basic.jc` - Basic say command examples
- `keep_basic.jc` - Basic variable examples
- `when_basic.jc` - Basic conditional examples
- `operators_basic.jc` - Basic arithmetic examples
- `operators_with_logic.jc` - Combined operators and conditions
