import numpy as np
import matplotlib.pyplot as plt


# 计算函数 f(x,y) = 5cos(xy) + xy + y^3 的最小值
# x ∈ [ -5, 5 ] y ∈ [-5，5 ]


class PSO:
    def __init__(self, iterTimes, groupSize, varNums, bound):
        '''
        :param iterTimes: 迭代次数
        :param groupSize: 解集大小
        :param varNums: 变量数量
        :param bound: 变量约束  [[x_min, y_min, z_min...] [x_max, y_max, z_max]]
        '''
        self.iterTimes = iterTimes
        self.groupSize = groupSize
        self.varNums = varNums
        self.bound = bound

        self.p_sites = np.zeros((self.groupSize, self.varNums))
        self.p_v = np.zeros((self.groupSize, self.varNums))
        self.p_optimal = np.zeros((self.groupSize, self.varNums))
        self.Optimal = np.zeros((1, self.varNums))
        self.alpha1, self.alpha2 = 1, 1
        self.weight = 0.5

        self.initialize()

    def initialize(self):
        temp_score = -1
        for i in range(self.groupSize):
            for j in range(self.varNums):
                # 1. 随机初始化粒子位置与速度
                self.p_sites[i][j] = np.random.uniform(self.bound[0][j], self.bound[1][j])
                self.p_v[i][j] = np.random.uniform(0, 1)
            # 2. 初始化粒子最好位置
            self.p_optimal[i] = self.p_sites[i]
            # 3. 评价当前粒子最好位置
            score = self.fitness(self.p_optimal[i])
            # 4. 更新全局最好位置
            if score > temp_score:
                self.Optimal = self.p_optimal[i]
                temp_score = score

    # 自定义函数
    def fitness(self, values):
        return (5 * np.cos(values[0] * values[1]) + values[0] * values[1] + pow(values[1], 3))

    # 更新位置与速度
    def update_params(self, group_size):
        for i in range(group_size):
            # 1. 更新速度
            self.p_v[i] = self.weight * self.p_v[i] + \
                          self.alpha1 * np.random.uniform(0, 1) * (self.p_optimal[i] - self.p_sites[i]) + \
                          self.alpha2 * np.random.uniform(0, 1) * (self.Optimal - self.p_sites[i])
            # 2. 更新位置
            self.p_sites[i] = self.p_sites[i] + self.p_v[i]
            # 3. 防止变量越界
            for j in range(self.varNums):
                if self.p_sites[i][j] < self.bound[0][j]:
                    self.p_sites[i][j] = self.bound[0][j]
                if self.p_sites[i][j] > self.bound[1][j]:
                    self.p_sites[i][j] = self.bound[1][j]
            # 4. 更新最优位置
            if self.fitness(self.p_sites[i]) > self.fitness(self.p_optimal[i]):
                self.p_optimal[i] = self.p_sites[i]
            if self.fitness(self.p_sites[i]) > self.fitness(self.Optimal):
                self.Optimal = self.p_sites[i]

    def run(self):
        scores = []
        self.tempOptimal = np.zeros((1, self.varNums))[0]
        for i in range(self.iterTimes):
            self.update_params(self.groupSize)
            scores.append(-self.fitness(self.Optimal))
            if self.fitness(self.Optimal) > self.fitness(self.tempOptimal):
                self.tempOptimal = self.Optimal.copy()
            print(f"{i}代 : {-self.fitness(self.tempOptimal)} : {self.tempOptimal}")
        self.display(scores)

    def display(self, data):
        plt.plot(range(self.iterTimes), data, color='lightcoral')
        plt.title("iteration - score", color='r')
        plt.xlabel("iteration")
        plt.ylabel("score")
        plt.show()


if __name__ == "__main__":
    bound = [[-5, -5], [5, 5]]
    pso = PSO(iterTimes=50, groupSize=20, varNums=2, bound=bound)
    pso.run()
