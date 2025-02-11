import matplotlib.pyplot as plt
import json

# Purely to plot the data for the bucket because matplotlib is fast and easy
def parse_time(time_str):
    # Split the value and unit, e.g., "2.4568 ms"
    value, unit = time_str.split()
    value = float(value)
    if unit == "us":
        return value / 1000
    elif unit == "ms":
        return value  
    elif unit == "s":
        return value * 1000  #convert seconds to milliseconds

if __name__ == "__main__":
    results = [] 
    samples = []
    means   = []

    # Load the data
    with open("data.json", "r") as f:
        data = json.load(f)

        for run in data["results"]:
            results.append(run["est_run_time"])
            samples.append(run["n"])
    
    results_parsed = [parse_time(x) for x in results]

    # Plot the data
    figure = plt.figure(figsize=(10, 6))
    plt.plot(samples, results_parsed)
    plt.xlabel("n size input")
    plt.ylabel("Time (ms)")
    plt.xticks([x for x in range(0, samples[-1] + 1, 10_000)])
    plt.grid()
    plt.title("MY Bucket Sort")
    plt.legend(["Estimated Run Time 100 samples"])

    # Save the plot   
    plt.savefig("../docs/bucket_sort.png")
