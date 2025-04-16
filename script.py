import os

def create_test_files(directory="TESTS", count=10, content="This is a test file for encryption.\n"):
    os.makedirs(directory, exist_ok=True)

    for i in range(1, count + 1):
        filename = os.path.join(directory, f"test{i}.txt")
        with open(filename, "w") as f:
            f.write(content * (i * 10))

    print(f"{count} test files created in '{directory}'.")

if __name__ == "__main__":
    create_test_files(count=100)