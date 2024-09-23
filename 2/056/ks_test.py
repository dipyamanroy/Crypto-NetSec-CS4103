import random

def ks_test(seeds):
    for seed in seeds:
        print(f"\nKS test with seed {seed}")
        
        # Set random seed
        random.seed(seed)
        
        # Generate random sequence of 30 floating-point numbers between 0 and 5
        sequence = [random.uniform(0, 5) for _ in range(30)]
        
        # Sort the sequence to compare cumulative distribution function (CDF)
        sorted_sequence = sorted(sequence)
        
        # Compute the D-statistic manually
        d_stat = 0
        for i, value in enumerate(sorted_sequence):
            # Theoretical CDF for uniform distribution in range [0, 5]
            theoretical_cdf = value / 5
            empirical_cdf = (i + 1) / len(sequence)
            d_stat = max(d_stat, abs(empirical_cdf - theoretical_cdf))
        
        # Manually computing critical values for the KS test at 95% and 99% confidence intervals
        ks_95 = 1.36 / (30**0.5)
        ks_99 = 1.63 / (30**0.5)
        
        print(f"KS statistic: {d_stat}")
        print(f"95% critical value: {ks_95}, 99% critical value: {ks_99}")
        print(f"Conclusion: {'Random' if d_stat < ks_95 else 'Not Random'} at 95% confidence")
        print(f"Conclusion: {'Random' if d_stat < ks_99 else 'Not Random'} at 99% confidence")