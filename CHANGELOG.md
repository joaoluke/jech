# Changelog

## [0.1.0] - 2025-05-31

### Added

- Support for multiple instructions in code `.jc`
- ASTList to represent a sequence of commands
- New compiler for multiple commands
- Updating the VM for sequential bytecode execution

### Changed

- Parser now returns list of ASTNodes
- File `main.c` reorganized and modularized

### Removed

- Limited support for a single instruction (single ASTNode)
