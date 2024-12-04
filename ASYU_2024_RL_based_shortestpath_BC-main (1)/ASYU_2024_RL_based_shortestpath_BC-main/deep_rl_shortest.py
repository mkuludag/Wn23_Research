import random
import numpy as np
import networkx as nx
import torch
import torch.nn as nn
import torch.optim as optim
from Transactions import Transactions
from read_matrices import read_matrices
import os
import matplotlib.pyplot as plt

random.seed(100)
np.random.seed(50)

# Define the Graph Transformer Model
class GraphTransformer(nn.Module):
    def __init__(self, input_dim, output_dim, num_heads=4, hidden_dim=128):
        super(GraphTransformer, self).__init__()
        self.fc_in = nn.Linear(input_dim, hidden_dim)
        self.transformer_layer = nn.TransformerEncoderLayer(d_model=hidden_dim, nhead=num_heads)
        self.fc_out = nn.Linear(hidden_dim, output_dim)

    def forward(self, x):
        x = self.fc_in(x)
        x = self.transformer_layer(x)
        x = self.fc_out(x)
        return x

# Epsilon-greedy policy (with visited nodes check)
def epsilon_greedy(s_curr, model, epsilon, visited):
    potential_next_states = np.where(np.array(D[s_curr]) > 0)[0]
    
    # Remove already visited nodes from potential next states
    unvisited_states = [state for state in potential_next_states if state not in visited]
    
    if not unvisited_states:
        return random.choice(potential_next_states)  # If no unvisited states, choose from all potential states
    
    if random.random() > epsilon:  # greedy
        q_values = model(torch.FloatTensor(D[s_curr]).unsqueeze(0))  # Get Q-values from the model
        s_next = unvisited_states[torch.argmax(q_values[0][unvisited_states]).item()]
    else:  # random select
        s_next = random.choice(unvisited_states)
    
    return s_next

# Save the model weights
def save_model_weights(model, file_path):
    torch.save(model.state_dict(), file_path)
    print(f"Model weights saved to {file_path}")

def read_transactions(file_path):
    all_transactions = []
    with open(file_path, 'r') as file:
        # İlk satırı oku ve atla (başlık satırı)
        headers = file.readline().strip().split('\t')
        
        # Geri kalan satırları işle
        for line in file:
            parts = line.strip().split('\t')
            if len(parts) == 7:
                PreviousAS = int(parts[0])
                CurrentAS = int(parts[1])
                NextAS = int(parts[2])
                Bandwidth = float(parts[3])
                Delay = float(parts[4])
                Hop = int(parts[5])
                Full_Path = parts[6]
                
                all_transaction = Transactions(PreviousAS, CurrentAS, NextAS, Bandwidth, Delay, Hop, Full_Path)
                all_transactions.append(all_transaction)
    return all_transactions


def find_current_as(all_transactions, value, bw):
    return [path for path in all_transactions if path.CurrentAS == value and path.Bandwidth >= bw]


def find_min_hop_for_current_as(all_transactions, currentAS, nextAS, bw):
    result = find_current_as(all_transactions, currentAS, bw)
    
    current_as_paths = [path for path in result if path.NextAS == nextAS]
    
    if not current_as_paths:
        current_as_paths = [path for path in result if path.PreviousAS == nextAS]
        if not current_as_paths:
            return -1
    
    min_hop_path = min(current_as_paths, key=lambda path: path.Hop)
    return min_hop_path


# Modify the train_graph_transformer function
def train_graph_transformer(model, num_epoch, bw, gamma=0.8, epsilon=0.05, alpha=0.1):
    print("Training the Graph Transformer model with multiple source-destination pairs...")
    optimizer = optim.Adam(model.parameters(), lr=0.01)
    criterion = nn.MSELoss()

    num_nodes = model.fc_in.in_features

    # For plotting
    epoch_losses = []
    accuracy_per_epoch = []

    # Create directory for saving plots
    plot_dir = "drl_training_figs"
    os.makedirs(plot_dir, exist_ok=True)

    for epoch in range(num_epoch):
        source = random.randint(0, num_nodes - 1)
        destination = random.randint(0, num_nodes - 1)
        while destination == source:
            destination = random.randint(0, num_nodes - 1)

        s_cur = source
        path = []
        visited = set()
        total_delay = 0
        losses = []
        correct_decisions = 0
        total_decisions = 0

        while True:
            visited.add(s_cur)
            s_next = epsilon_greedy(s_cur, model, epsilon, visited)

            hop = find_min_hop_for_current_as(all_transactions, s_cur, s_next, bw)
            delay = hop.Delay if hop != -1 else 9999
            reward = -D[s_cur][s_next] - (delay)

            q_values = model(torch.FloatTensor(D[s_cur]).unsqueeze(0))
            target_q = reward + gamma * q_values[0][s_next]

            loss = criterion(q_values[0][s_next], target_q)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            losses.append(loss.item())

            # Track accuracy: Did the model pick the shortest hop?
            predicted_next = torch.argmax(q_values[0]).item()
            if predicted_next == s_next:
                correct_decisions += 1
            total_decisions += 1

            s_cur = s_next
            path.append(s_cur)
            total_delay += delay

            if s_cur == destination:
                break

        # Log metrics for this epoch
        epoch_losses.append(np.mean(losses))
        accuracy = (correct_decisions / total_decisions) * 100 if total_decisions > 0 else 0
        accuracy_per_epoch.append(accuracy)

        print(f"Epoch {epoch + 1}/{num_epoch}: Loss={epoch_losses[-1]:.4f}, Accuracy={accuracy:.2f}%, "
              f"Source={source}, Destination={destination}, Path={path}, Total Delay={total_delay}")

    # Plot metrics
    plt.figure(figsize=(12, 5))

    # Loss plot
    plt.subplot(1, 2, 1)
    plt.plot(epoch_losses, label="Loss")
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.title("Training Loss")
    plt.legend()
    plt.savefig(os.path.join(plot_dir, "training_loss.png"))

    # Accuracy plot
    plt.subplot(1, 2, 2)
    plt.plot(accuracy_per_epoch, label="Accuracy")
    plt.xlabel("Epoch")
    plt.ylabel("Accuracy (%)")
    plt.title("Convergence of Accuracy")
    plt.legend()
    plt.savefig(os.path.join(plot_dir, "accuracy_convergence.png"))

    plt.tight_layout()
    plt.show()

    print(f"Plots saved to {plot_dir}/")

    return path, model

# Example usage
if __name__ == '__main__':
    # Path setup
    network = 'USNET'
    cur_path = os.getcwd()
    file_path = os.path.join(cur_path, network, 'network', 'adjacency_24_0_1_1_updated.txt') # adjacency_14_0_1_2_updated.txt
    D = read_matrices(file_path)
    num_nodes = len(D)

    # Read transactions
    transactions_file = os.path.join(cur_path, network, 'transactions', 'transactions_usnet_5nodes.txt') # 'transactions_nsfnet_5nodes.txt'   'transactions_usnet_5nodes.txt'
    all_transactions = read_transactions(transactions_file)

    # Example bandwidth demand
    bw = 25

    # Initialize Graph Transformer model
    model = GraphTransformer(input_dim=num_nodes, output_dim=num_nodes)

    path, model = train_graph_transformer(model, num_epoch=500, bw=bw)
    print("Path found:", path)

    save_model_weights(model, "graph_transformer_weights_USNET.pth")