#!/bin/bash

# Jech Git Hooks Installer
# This script installs Git hooks for the Jech project

echo "🔧 Installing Jech Git Hooks..."
echo ""

# Check if we're in a git repository
if [ ! -d ".git" ]; then
    echo "❌ Error: Not in a git repository"
    echo "Please run this script from the root of the Jech project"
    exit 1
fi

# Create hooks directory if it doesn't exist
mkdir -p .git/hooks

# Install pre-commit hook
if [ -f ".git/hooks/pre-commit" ]; then
    echo "⚠️  Pre-commit hook already exists"
    read -p "Do you want to overwrite it? (y/n) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "Installation cancelled"
        exit 0
    fi
fi

# Copy and make executable
cp .git/hooks/pre-commit .git/hooks/pre-commit.backup 2>/dev/null
cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash

# Jech Pre-Commit Hook
# Runs tests before allowing a commit to ensure code quality

echo "🔍 Running pre-commit checks..."
echo ""

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Check if build directory exists
if [ ! -d "build" ]; then
    mkdir -p build
fi

# Compile the project
echo "🔨 Compiling Jech..."
make > /dev/null 2>&1

if [ $? -ne 0 ]; then
    echo -e "${RED}✗ Compilation failed!${NC}"
    echo "Fix compilation errors before committing."
    exit 1
fi

echo -e "${GREEN}✓ Compilation successful${NC}"
echo ""

# Run tests
echo "🧪 Running test suite..."
./run_tests.sh > /tmp/jech_test_output.txt 2>&1

if [ $? -ne 0 ]; then
    echo -e "${RED}✗ Tests failed!${NC}"
    echo ""
    echo "Test output:"
    cat /tmp/jech_test_output.txt
    echo ""
    echo -e "${RED}════════════════════════════════════════${NC}"
    echo -e "${RED}  Commit blocked - fix failing tests${NC}"
    echo -e "${RED}════════════════════════════════════════${NC}"
    rm /tmp/jech_test_output.txt
    exit 1
fi

echo -e "${GREEN}✓ All tests passed!${NC}"
echo ""

# Clean up
rm -f /tmp/jech_test_output.txt

echo -e "${GREEN}════════════════════════════════════════${NC}"
echo -e "${GREEN}  ✓ Pre-commit checks passed!${NC}"
echo -e "${GREEN}  Proceeding with commit...${NC}"
echo -e "${GREEN}════════════════════════════════════════${NC}"
echo ""

exit 0
EOF

chmod +x .git/hooks/pre-commit

echo "✅ Pre-commit hook installed successfully!"
echo ""
echo "📝 What happens now:"
echo "  • Every time you run 'git commit', tests will run automatically"
echo "  • If tests fail, the commit will be blocked"
echo "  • If tests pass, the commit proceeds normally"
echo ""
echo "💡 Tips:"
echo "  • To skip the hook temporarily: git commit --no-verify"
echo "  • To uninstall: rm .git/hooks/pre-commit"
echo ""
echo "🎉 You're all set!"
