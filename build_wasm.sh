#!/bin/bash

# Script to build Jech WASM and copy to platform

set -e

echo "🔨 Building Jech WebAssembly..."

# Build WASM
make wasm

echo "✅ WASM build complete!"

# Check if platform directory exists
PLATFORM_DIR="../jech-platform/public/wasm"

if [ -d "$PLATFORM_DIR" ]; then
    echo "📦 Copying WASM files to platform..."
    
    # Copy WASM files
    cp build/jech.wasm "$PLATFORM_DIR/"
    cp build/jech.js "$PLATFORM_DIR/"
    
    echo "✅ Files copied successfully!"
    echo ""
    echo "Files copied:"
    echo "  - jech.wasm"
    echo "  - jech.js"
    echo ""
    echo "🚀 You can now run the platform with: cd ../jech-platform && npm run dev"
else
    echo "⚠️  Platform directory not found: $PLATFORM_DIR"
    echo "Please make sure the jech-platform directory exists"
    exit 1
fi
