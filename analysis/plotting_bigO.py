import matplotlib.pyplot as plt
import json

if __name__ == "__main__":
    # Initialize the data
    type_results = ["results_int", "results_float", "results_improved_ints", "results_improved_floats"]
    colors = ["blue", "red", "green", "orange"]
    legends = ["Integer sort", "Float sort", "Improved integer sort", "Improved float sort"]
    samples = [10, 100, 1_000, 10_000, 100_000]
    figure = plt.figure(figsize=(10, 6))
    
    # Load the data
    with open("data.json", "r") as f:
        data = json.load(f)
    
        for i, test in enumerate(type_results):
            plt.plot(samples, data[test], color=colors[i], label=legends[i])
    
    plt.xlabel("n size input")
    plt.ylabel("Time (ms)")
    plt.xticks([x for x in range(0, samples[-1] + 1, 10_000)])
    plt.yticks([x for x in range(0, 8000, 500)])
    plt.grid()
    plt.legend()
    plt.title("Bucket Sort-algorithm")

    # Save the plot   
    plt.savefig("../docs/images/bucket_sort.png")
