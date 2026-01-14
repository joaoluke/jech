# Security Policy

## Supported Versions

JECH is an educational project under active development. Currently, only the latest version from the `main` branch receives security updates.

| Version | Supported          |
| ------- | ------------------ |
| main    | :white_check_mark: |
| < 1.0   | :x:                |

## Reporting a Vulnerability

If you discover a security vulnerability in JECH, please help us keep the project secure by following these guidelines:

### How to Report

1. **DO NOT** open a public issue for security vulnerabilities
2. Send an email to the project maintainer with:
   - Detailed description of the vulnerability
   - Steps to reproduce the issue
   - Potential impact
   - Suggested fixes (if any)

### What to Expect

- **Acknowledgment**: You will receive a receipt confirmation within 48 hours
- **Assessment**: We will assess the vulnerability within 7 days
- **Fix**: We will work on a fix and keep you informed
- **Disclosure**: We will coordinate public disclosure after the fix

### Scope

This project is primarily educational. Relevant vulnerabilities include:

- Arbitrary code execution
- Buffer overflows
- Critical memory leaks
- Code injection through `.jc` files
- VM security issues

### Recognition

Contributors who report valid security vulnerabilities will be acknowledged in the CHANGELOG (if desired).

## Best Practices

When using JECH:

- ✅ Use only for educational purposes
- ✅ Execute `.jc` files only from trusted sources
- ✅ Keep the project updated
- ❌ Do not use in production environments
- ❌ Do not execute untrusted code

## Known Security Limitations

As an educational project, JECH has intentional limitations:

- No execution sandbox
- No strict input validation
- Simplified memory management
- No protection against malicious code

**JECH is not suitable for production use.**

---

Thank you for helping keep JECH secure! 🔒
