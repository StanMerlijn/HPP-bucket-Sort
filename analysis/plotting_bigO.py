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
    type_results = ["results_int", "results_float"]
    colors = ["blue", "red"]
    legends = ["Integar sort", "Float sort"]
    figure = plt.figure(figsize=(10, 6))
    
    # Load the data
    with open("data.json", "r") as f:
        data = json.load(f)
    
        for i, test in enumerate(type_results):
            results = [] 
            samples = []

            for run in data[test]:
                results.append(run["est_run_time"])
                samples.append(run["n"])

            results_parsed = [parse_time(x) for x in results]
            plt.plot(samples, results_parsed, color=colors[i], label=legends[i])


    # Plot the data
    plt.xlabel("n size input")
    plt.ylabel("Time (ms)")
    plt.xticks([x for x in range(0, samples[-1] + 1, 10_000)])
    plt.grid()
    plt.legend()
    plt.title("MY Bucket Sort")

    # Save the plot   
    plt.savefig("../docs/images/bucket_sort.png")
