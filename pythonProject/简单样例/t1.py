import numpy as np
import matplotlib.pyplot as plt

# 参数
num_of_cars = 30
road_length = 100
max_speed = 5
deceleration_probability = 0.3
num_of_steps = 50

# 初始化
speeds = np.random.randint(0, max_speed + 1, size=num_of_cars)
positions = np.sort(np.random.choice(range(road_length), size=num_of_cars, replace=False))

# 用于可视化
history_positions = np.zeros((num_of_steps, road_length))

# 模拟
for step in range(num_of_steps):
    # 加速
    speeds = np.minimum(speeds + 1, max_speed)

    # 减速避免碰撞
    for i in range(num_of_cars):
        distance_to_next_car = (positions[(i + 1) % num_of_cars] - positions[i] - 1) % road_length
        speeds[i] = min(speeds[i], distance_to_next_car)

    # 随机减速
    random_deceleration = (np.random.rand(num_of_cars) < deceleration_probability)
    speeds = np.maximum(speeds - random_deceleration, 0)

    # 移动车辆
    positions = (positions + speeds) % road_length

    # 记录位置
    history_positions[step, positions] = 1

    # 可视化当前的交通状况
plt.figure(figsize=(10, 8))
plt.imshow(history_positions, cmap='Greys', interpolation='none')
plt.title('Traffic Simulation (Nagel-Schreckenberg Model)')
plt.xlabel('Position on Road')
plt.ylabel('Time Step')
plt.show()

