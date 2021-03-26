import numpy as np
import matplotlib.pyplot as plt


# 计算函数 f(x,y) = 5cos(xy) + xy + y^3 的最小值
# x ∈ [ -5, 5 ] y ∈ [-5，5 ]
class Particle:
    def __init__(self, res):
        self.res = res
        self.score = -1


class SA:
    def __init__(self, scoreFunc):
        # 评分函数
        self.scoreFunc = scoreFunc
        # 退火速率
        self.lamda = 0.9
        # 初始温度
        self.T = 1000
        # 终止条件
        self.Tmin = 1
        # 解集
        self.Solutions = []
        # 解数量
        self.solutionNums = 20
        # 最优解
        self.Optimal = None
        # 局部最优解
        self.localOptimal = None
        # 每个 T的迭代次数
        self.iterTimes = 100
        # 系数 K
        self.K = 1

        self.initialize()

    # 初始化
    def initialize(self):
        self.Solutions = []
        self.T = 1000
        # 根据变量范围生成初始解
        for i in range(self.solutionNums):
            res = [np.random.uniform(-5, 5), np.random.uniform(-5, 5)]
            particle = Particle(res)
            self.Solutions.append(particle)

    # 评价解集
    def score(self):
        self.localOptimal = self.Solutions[0]
        for particle in self.Solutions:
            # 1. 计算能量
            particle.score = self.scoreFunc(particle)
            # 2. 更新全局最优解
            if particle.score > self.Optimal.score:
                self.Optimal = particle
            # 3. 更新局部最优解
            if particle.score > self.localOptimal.score:
                self.localOptimal = particle

    # 交换概率
    def Probability(self, p_old, p_new):
        if p_new.score > p_old.score:
            return 1
        else:
            return np.exp((p_old.score - p_new.score) / (self.K * self.T))

    # 在当前解附近搜索新解
    def search(self, p):
        x = sorted([-5, 5, p.res[0] + np.random.uniform(-1, 1)])[1]
        y = sorted([-5, 5, p.res[1] + np.random.uniform(-1, 1)])[1]
        p_new = Particle([x, y])
        return p_new

    # 迭代过程
    def iteration(self):
        n = 0
        while n <= self.iterTimes:
            # 1. 计算解集评分
            self.score()
            # 2. 扰动解集
            for i in range(self.solutionNums):
                p = self.Solutions[i]
                p_new = self.search(p)
                # 3. 依概率更新解集
                if (np.random.random() < self.Probability(p, p_new)):
                    self.Solutions[i] = p_new
            n += 1

    # 降温
    def cooling(self):
        # 初始化
        g_scores, l_scores = [], []
        self.Optimal = self.Solutions[0]
        # 1. 判断终止条件
        while self.T > self.Tmin:
            # 2. 该温度下迭代
            self.iteration()
            # 3. 记录当前温度下的局部最优解
            print(f'{round(self.T, 5)}:{-round(self.localOptimal.score, 5)}:{self.localOptimal.res}')
            g_scores.append(-round(self.Optimal.score, 4))
            l_scores.append(-round(self.localOptimal.score, 4))
            # 4. 降温
            self.T *= self.lamda
        print(f"最优解：{self.Optimal.res}:{-round(self.Optimal.score, 4)}")
        self.display(g_scores, l_scores)

    # 结果可视化
    def display(self, res1, res2):
        fig, ax = plt.subplots(1, 2, figsize=(10, 4))
        ax[0].plot(res1, color='lightcoral')
        ax[0].set_title("Global Optimal", color='r')
        ax[0].set_xlabel("iteration")
        ax[0].set_ylabel("score")

        ax[1].plot(res2, color='#4b5cc4')
        ax[1].set_title("Local Optimal", color='r')
        ax[1].set_xlabel("iteration")
        ax[1].set_ylabel("score")
        plt.show()


if __name__ == "__main__":
    sa = SA(lambda p: -(5 * np.cos(p.res[0] * p.res[1]) + p.res[0] * p.res[1] + pow(p.res[1], 3)))
    sa.cooling()

    
