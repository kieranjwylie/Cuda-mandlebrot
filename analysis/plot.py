import argparse
import matplotlib.pyplot as plt
import numpy as np
###############################################################################
def parse_args():
    parser = argparse.ArgumentParser(description="Plotting script")
    parser.add_argument("-i", "--input", type=str, default = "mandlebrot.txt", help="Input data file")
    parser.add_argument("-o", "--output", type=str, default = "mandle.png", help="Output plot file")
    return parser.parse_args()
###############################################################################
def load_data(file):
    data = np.loadtxt(file, unpack = True)
    return data
###############################################################################
def plot_mandle(data, font_small = 20, font_large = 30, figx = 16, figy = 12):
    fig, ax = plt.subplots(figsize=(figx, figy))
    ax.scatter(data[0], data[1], s = 0.1, c = data[2])
    ax.set_xlabel('Re', fontsize = font_large)
    ax.set_ylabel('Im', fontsize = font_large)
    plt.show()
    return
################################################################################
def main():
    args = parse_args()
    data = load_data(args.input)
    plot_mandle(data)
###############################################################################
if __name__ == "__main__":
    main()