import uproot
import matplotlib.pyplot as plt
import numpy as np

def braggs_curve():
    samples = ["PP_ZnS_", "TPP2MnBr4_"]
    energies = ["0_38", "0_7", "1", "3"]

    for sample in samples:
        for energy in energies:
            file = uproot.open(f"../build/{sample}{energy}.root")
            hist = file["Bragg peak"]
            values, edges = hist.to_numpy()
            with open(f"{sample}_{energy}_bragg_peak.txt", "w") as f:
                for value, edge in zip(values, edges[:-1]):
                    f.write(f"{edge}\t{value}\n")

def make_spectrum_plot():
    file = uproot.open("../build/TPP2MnBr4_3mm_45millions.root")
    hist = file["Spectrum"]
    values, edges = hist.to_numpy()
    mean_energy = np.average(edges[:-1], weights=values)
    print(f"Mean Energy: {mean_energy} MeV")
    plt.figure(figsize=(10, 6))
    
    plt.yscale('log')
    plt.xlabel("Energy, [MeV]")
    plt.ylabel("Counts")
    plt.title("Energy Spectrum")
    plt.grid(True)
    plt.hist(edges[:-1], bins=edges, weights=values, histtype='step')
    plt.show()
    
if __name__ == "__main__":
    braggs_curve()
    make_spectrum_plot()
    file = uproot.open("../build/MAPbBr3_2mm_full.root")
    beam_energy = file["Beam"]["Energy"].array()
    edep = file["Crystal"]["Edep"].array()
    event_id = file["Crystal"]["EventID"].array()
    edep = file['Crystal']['Edep'].array()
    event_id = file['Crystal']['EventID'].array()
    particle_id = file['Crystal']['ParticleID'].array()
    primary_energy = file['Crystal']['PrimaryEnergy'].array()

    edep_sum = {}
    beam = []

    for i in range(len(event_id)):
        if event_id[i] in edep_sum:
            edep_sum[event_id[i]] += edep[i]
        else:
            beam.append(primary_energy[i])
            edep_sum[event_id[i]] = edep[i]

    total_edep_list = []
    for event, total_edep in edep_sum.items():
        total_edep_list.append(total_edep)
        if event == 491965:
            print(f"Event ID: {event}, Total Edep: {total_edep}")
    
    plt.hist2d(beam, total_edep_list, bins=(100,100))
    plt.ylim(0,0.01)
    plt.xlim(0,0.25)
    plt.show()

    sample_names = ["PP_ZnS", "TPP2MnBr4_film", "TPP2MnBr4_single", "Gua3SbCl6"]
    x = [100, 500,1000, 1500, 2000,2500, 3000, 3500, 4000, 4500, 5000]
    y = []
    x,y = [],[]
    with open('interaction.txt', 'r') as file:
        for i, line in enumerate(file.readlines()[1:]):
            try:
                x.append(int(line.split()[0]))
                y.append(float(line.split()[1]))
            except:
                continue
    x = x[:11]
    
    for sample in sample_names:
        for file in x:
            file = uproot.open(f"../build/{sample}/{file}.root")
            y = np.append(y, 100 * np.sum(file["Crystal"]['Edep'].array()) / np.sum(file["Beam"]["Energy"].array()))

    for sample in sample_names:
        for file in x:
            file = uproot.open(f"../build/{sample}/{file}.root")
            y = np.append(y, len(np.unique(file["Crystal"]['EventID'].array(), return_counts=True)[1])/1e6*100)
    with open("interaction.txt", 'w') as file: #
        for i, name in enumerate(sample_names):
            file.write(f'{name}\n')
            for j, d in enumerate(x):
                file.write(f'{d}\t{y[i*len(x)+j]}\n')

    plt.plot(x, y[:len(x)], label=r"PPZnS")
    plt.scatter(x, y[:len(x)], color='blue', zorder=5)
    
    plt.plot(x, y[len(x):2*len(x)], label=r"TPP$_2$MnBr$_4$")
    plt.scatter(x, y[len(x):2*len(x)], color='orange', zorder=5)

    plt.plot(x, y[2*len(x):3*len(x)], label=r"TPP$_2$MnBr$_4$ single crystal")
    plt.scatter(x, y[2*len(x):3*len(x)], color='Green', zorder=5)
    

    plt.plot(x, y[3*len(x):4*len(x)], label=r"Gua$_3$SbCl$_6$")
    plt.scatter(x, y[3*len(x):4*len(x)], color='Red', zorder=5)

    # plt.ylabel(r"Absorbed energy fraction, [%]")
    plt.ylabel(r"Neutnrons with interactions, [%]")
    plt.xlabel(r"d, [$\mu$m]")
    plt.grid(True)
    plt.legend()
    plt.show()