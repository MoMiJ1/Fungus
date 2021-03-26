import numpy as np
import matplotlib.pyplot as plt
import random


class GA_extremum:

    # 求解 x*sin(2x)*e^(-0.5x) 在 0<=x<=1 时的最大值
    # 使用浮点数编码

    def __init__(self, M_Size, T, Pc, Pm, bound_min, bound_max):
        '''
        :param M_Size: 种群数量
        :param T: 遗传代数
        :param Pc: 交叉概率
        :param Pm: 变异概率
        :param bound_min: 搜素上届
        :param bound_max: 搜索下界
        '''
        self.M_Size = M_Size
        self.T = T
        self.Pc = Pc
        self.Pm = Pm
        self.bound_min = bound_min
        self.bound_max = bound_max

        self.Optimal = [0, 0]

    # 随机生成初始解
    def initM(self):
        return [np.random.uniform(self.bound_min, self.bound_max) for i in range(self.M_Size)]

    # 目标函数
    def myfunc(self, x):
        return x * np.sin(2 * x) * np.exp(-0.5 * x)

    # 适应度函数
    def fitness(self, M):
        return [self.myfunc(M[i]) for i in range(self.M_Size)]

    # 选择: 最优保存选择
    def select(self, fitness, M):
        if np.max(fitness) > self.Optimal[1]:
            self.Optimal = [M[np.argmax(fitness)], np.max(fitness)]
        fitness[np.argmin(fitness)] = self.Optimal[1]
        M[np.argmin(fitness)] = M[np.argmax(fitness)]
        return fitness, M

    # 算术交叉
    def cross(self, M):
        s = []
        for i in range(self.M_Size // 2):
            if np.random.random() < self.Pc:
                x1 = np.random.randint(0, self.M_Size)
                while x1 in s:
                    x1 = np.random.randint(0, self.M_Size)
                x2 = np.random.randint(0, self.M_Size)
                while x2 in s:
                    x2 = np.random.randint(0, self.M_Size)
                s.append(x2)
                a, b = M[x1], M[x2]
                alpha = np.random.uniform(0, 0.05)
                M[x1] = sorted([np.random.choice([-1, 1]) * alpha * b + (1 - alpha) * a, 0, 1])[1]
                M[x2] = sorted([np.random.choice([-1, 1]) * alpha * a + (1 - alpha) * b, 0, 1])[1]
        return M

    # 变异
    def mutation(self, M, t):
        if t < 0.8 * self.T:
            for i in range(self.M_Size):
                if np.random.random() < self.Pm:
                    M[i] = np.random.uniform(self.bound_min, self.bound_max)
        else:
            for i in range(self.M_Size):
                if np.random.random() < self.Pm:
                    M[i] = sorted([M[i] + np.random.choice([-1, 1]) * random.gauss(
                        (self.bound_min + self.bound_max) / 2, 2 * (self.bound_max - self.bound_min) / self.M_Size), 0,
                                   1])[1]
        return M

    def run(self):
        M = self.initM()
        t = 1
        while t <= self.T:
            fitness = self.fitness(M)
            fitness, M = self.select(fitness, M)
            M = self.cross(M)
            M = self.mutation(M, t)
            t += 1


if __name__ == "__main__":
    ga = GA_extremum(M_Size=40, T=50, Pm=0.05, Pc=0.5, bound_min=0, bound_max=1)
    res = ga.run()
    print("最优解为：x={}\n极值：{}".format(res[0], res[1]))
