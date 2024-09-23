import platform
from chi_square_test import chi_square_test
from ks_test import ks_test

# Array of 13 random seeds
seeds = [1023, 7654, 1111, 2233, 9876, 4536, 9087, 1223, 3746, 6598, 2019, 8765, 4321]

# Print OS and Kernel details
def print_system_info():
    print("\nSystem Information:")
    print(f"Operating System: {platform.system()} {platform.release()}")
    print(f"Kernel Version: {platform.version()}")

if __name__ == "__main__":
    print_system_info()
    chi_square_test(seeds)
    ks_test(seeds)
