import matplotlib.pyplot as plt
from matplotlib.patches import Arc

dots = []
seq = []
with open('./static/data/dotBracNotation.txt', 'r') as file:
    content = file.read()
for i in content:
    dots.append(i)
dots = dots[0:-1]

with open('./static/data/input.txt', 'r') as file:
    content = file.read()
for i in content:
    seq.append(i)

def plot_rna_structure(dot_bracket, sequence):
    # Calculate the total number of nucleotides
    num_nucleotides = len(dot_bracket)
    maxh = 1
    # Scatter points in a straight line
    x = range(num_nucleotides)
    y = [0] * num_nucleotides
    
    plt.scatter(x, y, color='black')  # Scatter points
    
    # Connect points with line segments
    for i in range(num_nucleotides - 1):
        plt.plot([x[i], x[i+1]], [y[i], y[i+1]], color='black')
    
    # Connect bracket pairs with arcs
    stack = []
    for i, char in enumerate(dot_bracket):
        if char == '(':
            stack.append(i)
        elif char == ')':
            start_index = stack.pop()
            end_index = i
            if end_index-start_index > maxh:
                maxh = end_index-start_index
            arc = Arc(((start_index+end_index)/2,0), end_index-start_index, 0.05*(end_index-start_index), angle=0, theta1=0, theta2=180, color='red')
            plt.gca().add_patch(arc)
    
    # Add text annotations below each point
    for i, (x_coord, nucleotide) in enumerate(zip(x, sequence)):
        plt.text(x_coord, -0.1, nucleotide, ha='center', va='top')
    
    plt.xlim(-1, num_nucleotides)
    plt.ylim(-1, 0.07*maxh)
    plt.gca().axes.get_yaxis().set_visible(False)
    plt.savefig('./static/Images/dotbrac.png')

plot_rna_structure(dots, seq)