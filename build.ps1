# Get all .c files in the current directory
$files = Get-ChildItem *.c | ForEach-Object { $_.Name }

# Compile the files with gcc
gcc $files -o main

# Check if the build was successful
if ($LASTEXITCODE -eq 0) {
    Write-Output "Build successful. Running main..."
    ./main
} else {
    Write-Output "Build failed."
}
