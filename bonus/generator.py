import random
import sys

def generate_aircraft_data(num_aircrafts):
    aircraft_data = []
    for _ in range(num_aircrafts):
        departure_x = random.randint(1, 1920)
        departure_y = random.randint(1, 1080)
        arrival_x = random.randint(1, 1920)
        arrival_y = random.randint(1, 1080)
        speed = random.randint(5, 30)
        delay = random.randint(1, 10)
        aircraft_data.append(f"A {departure_x - 1} {departure_y - 1} {arrival_x - 1} {arrival_y - 1} {speed - 1} {delay - 1}")
    return aircraft_data

def generate_control_tower_data(num_towers):
    tower_data = []
    for _ in range(num_towers):
        x = random.randint(1, 1920)
        y = random.randint(1, 1080)
        radius = random.randint(1, 10)
        tower_data.append(f"T {x} {y} {radius}")
    return tower_data

def write_to_file(filename, aircraft_data, tower_data):
    with open(filename, "w") as file:
        for data in aircraft_data + tower_data:
            file.write(data + "\n")

def main():
    if len(sys.argv) != 3:
        print("Usage: ./generator.py [nb_plane] [nb_towers]")
        return 84
    try:
        num_aircrafts = int(sys.argv[1])
        num_towers = int(sys.argv[2])
    except ValueError:
        print("Please enter valid values for [nb_plane] and [nb_towers].")
        exit(84)
    filename = "example.txt"
    aircraft_data = generate_aircraft_data(num_aircrafts)
    tower_data = generate_control_tower_data(num_towers)
    write_to_file(filename, aircraft_data, tower_data)
    print(f"Script generated in {filename}")
if __name__ == "__main__":
    main()
