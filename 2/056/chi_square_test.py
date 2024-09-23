import random

def chi_square_test(seeds):
    for seed in seeds:
        print(f"\nChi-square test with seed {seed}")
        
        # Set random seed
        random.seed(seed)
        
        # Generate random sequence of 5000 integers between 1 and 1000
        sequence = [random.randint(1, 1000) for _ in range(5000)]
        
        # Calculate observed frequencies
        observed = [0] * 1000
        for num in sequence:
            observed[num - 1] += 1
        
        # Expected frequency for each number (since uniform distribution is expected)
        expected = len(sequence) / 1000
        
        # Compute chi-square statistic manually
        chi_square_stat = sum([(o - expected)**2 / expected for o in observed])
        
        # Degrees of freedom (1000 categories - 1)
        df = 999
        
        # Manually computing the chi-square critical values for 95% and 99% confidence intervals
        # Approximate values taken from chi-square table
        chi2_95 = 1074  # Corresponding to df = 999
        chi2_99 = 1097
        
        print(f"Chi-square statistic: {chi_square_stat}")
        print(f"95% critical value: {chi2_95}, 99% critical value: {chi2_99}")
        print(f"Conclusion: {'Random' if chi_square_stat < chi2_95 else 'Not Random'} at 95% confidence")
        print(f"Conclusion: {'Random' if chi_square_stat < chi2_99 else 'Not Random'} at 99% confidence")