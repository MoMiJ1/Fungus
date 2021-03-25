import numpy as np
import matplotlib.pyplot as plt


# 个体类
class Indv:
    # 传入个体的基因
    def __init__(self, gene):
        self.gene = gene
        self.score = -1


class GA:
    def __init__(self, Pc, Pm, indvNums, scoreFunc, geneLength):
        # 交叉概率
        self.Pc = Pc
        # 变异概率
        self.Pm = Pm
        # 个体数量
        self.indvNums = indvNums
        # 适应度函数
        self.scoreFunc = scoreFunc
        # 基因长度
        self.geneLength = geneLength
        # 种群
        self.Groups = []
        # 迭代次数
        self.t = 0
        # 最优个体
        self.Optimal = None
        # 交叉数量
        self.crossNums = 0
        # 变异数量
        self.mutationNums = 0
        # 适应度之和
        self.scoreSum = 0.0

        self.initialize()

    def initialize(self):
        self.Groups = []
        for i in range(self.indvNums):
            # 1. gene = [0,1,2...genelength]
            gene = [i for i in range(self.geneLength)]
            # 2. 打乱 gene
            np.random.shuffle(gene)
            # 3. 新个体
            indv = Indv(gene)
            self.Groups.append(indv)

    # 计算适应度
    def fitness(self):
        # 1. 初始化
        self.scoreSum = 0.0
        self.Optimal = self.Groups[0]
        for indv in self.Groups:
            # 2. 计算个体适应度
            indv.score = self.scoreFunc(indv)
            self.scoreSum += indv.score
            # 3. 更新最优个体
            if self.Optimal.score > indv.score:
                self.Optimal = indv

    # 交叉
    def cross(self, dad, mom):
        son, position = [], 0
        # 1. 确定交叉片段位置
        index1 = np.random.randint(0, self.geneLength - 1)
        index2 = np.random.randint(0, self.geneLength - 1)
        segment = mom.gene[index1: index2]
        for x in dad.gene:
            # 2. 到达交叉起点
            if position == index1:
                son.extend(segment)
                position += 1
            # 3. 其它情况，直接将基因插入子代 gene
            if x not in son:
                son.append(x)
                position += 1
        self.crossNums += 1
        return son

    # 变异
    def mutation(self, gene):
        son = gene[:]
        # 1. 确定变异点
        index1 = np.random.randint(0, self.geneLength - 1)
        index2 = np.random.randint(0, self.geneLength - 1)
        # 2. 交换两点基因
        son[index1], son[index2] = son[index2], son[index1]
        self.mutationNums += 1
        return son

    # 选择
    def select(self):
        # 1. 利用总适应度选择
        s = np.random.uniform(0, self.scoreSum)
        for indv in self.Groups:
            s -= indv.score
            if s <= 0:
                return indv
        raise Exception("Error", self.scoreSum)

    # 产生新子代
    def generate(self):
        dad = self.select()
        # 1. 交叉
        P = np.random.random()
        if P < self.Pc:
            mom = self.select()
            gene = self.cross(dad, mom)
        else:
            gene = dad.gene
        # 2. 变异
        P = np.random.random()
        if P < self.Pm:
            gene = self.mutation(gene)
        return Indv(gene)

    # 产生新种群
    def evolve(self):
        # 1. 计算适应度
        self.fitness()
        # 2. 新一代
        groups = [self.Optimal]
        # 3. 产生新子代
        while len(groups) < self.indvNums:
            groups.append(self.generate())
        # 4. 更新种群
        self.Groups = groups
        self.t += 1


class TSP:
    def __init__(self, indvNums):
        self.indvNums = indvNums
        self.initialize()
        self.ga = GA(Pc=0.7, Pm=0.1, indvNums=self.indvNums, geneLength=len(self.sites), scoreFunc=self.scoreFunc())

    # 初始化
    def initialize(self):
        self.sites = []
        # 随机生成点
        for i in range(100):
            x = np.random.randint(0, 200)
            y = np.random.randint(0, 200)
            self.sites.append((x, y))

    # 计算某基因（路径）的总距离
    # 适应度函数
    def distance(self, gene):
        dist = 0.0
        for i in range(-1, len(self.sites) - 1):
            index1, index2 = gene[i], gene[i+1]
            site1, site2 = self.sites[index1], self.sites[index2]
            # 欧式距离
            dist += np.sqrt(pow(site1[0] - site2[0], 2) + pow(site1[1] - site2[1], 2))
        return dist/1000

    def scoreFunc(self):
        return lambda indv: self.distance(indv.gene)

    # 运行函数
    def run(self, T = 0):
        res, n = [], 0
        # 1. 判断终止条件
        while n < T:
            # 2. 生成新种群
            self.ga.evolve()
            # 3. 计算当前迭代最优结果
            dist = self.distance(self.ga.Optimal.gene)
            print(f'{self.ga.t} : {round(dist,5)}')
            res.append(dist)
            n += 1
        self.view(res, T)

    # 结果可视化
    def view(self, res, T):
        plt.plot(range(T),res, color='lightcoral')
        plt.title("iteration - score", color='r')
        plt.xlabel("iteration")
        plt.ylabel("score ×10^3")
        plt.show()


if __name__ == "__main__":
    tsp = TSP(100)
    tsp.run(500)
