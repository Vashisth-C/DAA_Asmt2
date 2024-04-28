if [ ! -f "$1" ]; then
    echo "Usage: $0 <requirements_file>"
    exit 1
fi

while IFS= read -r package; do
    sudo apt install -y "$package"
done < "$1"