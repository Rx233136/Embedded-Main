# 贡献指南与提交流程

> 本文档面向所有向本仓库提交资料的同学。请先通读再操作。

---

## 一、前置准备

### 1.1 生成 SSH 密钥

如果你还没有 SSH 密钥，在本地执行：

```bash
ssh-keygen -t ed25519 -C "你的姓名或昵称" -f ~/.ssh/id_ed25519
```

Windows 用户使用 Git Bash 或 PowerShell 均可。

### 1.2 提交公钥给管理员

将公钥内容发送给管理员：

```bash
cat ~/.ssh/id_ed25519.pub
```

管理员会将其添加到服务器的 `authorized_keys` 中。添加完成后，你就可以通过 SSH 访问仓库了。

### 1.3 克隆仓库

```bash
git clone ssh://Administrator@192.168.21.1/D:/GitRepos/lab-materials.git
cd lab-materials
```

---

## 二、分支策略（重要！）

本仓库对 `main` 分支有保护：**禁止直接 push，必须通过 squash merge 合并。**

### 为什么这样设计？

- 保持 `main` 分支历史干净、线性，方便追溯
- 避免功能分支的零散提交污染主分支
- 每个合并点对应一个完整的资料单元，便于回滚

### 你的工作流程

```bash
# Step 1: 确保 main 是最新的
git checkout main
git pull origin main

# Step 2: 创建功能分支（命名要有意义）
git checkout -b docs/新增-stm32-定时器笔记
git checkout -b fix/修正-linux-进程调度笔误
git checkout -b add/添加-2026-电赛-资料

# Step 3: 在该分支上工作、提交
# ... 编辑文件 ...
git add .
git commit -m "docs: 新增 STM32 定时器中断详解"

# Step 4: 回到 main，拉取最新（防止冲突）
git checkout main
git pull origin main

# Step 5: Squash 合并你的分支
git merge --squash docs/新增-stm32-定时器笔记

# Step 6: 提交合并后的变更
git commit -m "docs: 新增 STM32 定时器中断详解"

# Step 7: 推送到远程
git push origin main
```

### 如果直接 push 会怎样？

你会看到类似下面的拒绝信息：

```
[ERROR] Direct push to main/master is not allowed.
        You must use squash merge to merge feature branches.

Workflow:
  1. git checkout -b feature/xxx
  2. work on feature branch...
  3. git checkout main
  4. git merge --squash feature/xxx
  5. git commit -m 'feat: xxx'
  6. git push origin main
```

不用担心，按照上述流程重新操作即可。

---

## 三、提交规范

### 3.1 Commit Message 格式

采用 [Conventional Commits](https://www.conventionalcommits.org/) 简化版：

```
<type>: <简短描述>

<详细说明（可选）>
```

| 类型 | 用途 |
|------|------|
| `docs` | 新增或修改文档、笔记、面经 |
| `add` | 新增资料、项目文件 |
| `fix` | 修正错误、更新过时内容 |
| `reorg` | 目录结构调整、文件重命名 |

**示例**：
```
docs: 新增 FreeRTOS 任务调度八股

包含任务状态机、优先级反转、调度算法对比，
参考正点原子教程和官方文档整理。

fix: 修正 STM32 时钟树笔误
- HSE 频率应为 8MHz，原文写成 12MHz
- 补充 PLL 倍频系数说明
```

### 3.2 分支命名规范

```
<type>/<简短描述>
```

| 前缀 | 用途 |
|------|------|
| `docs/` | 新增/修改文档 |
| `add/` | 新增资料文件 |
| `fix/` | 修正内容错误 |
| `reorg/` | 目录结构调整 |

---

## 四、资料提交规范

### 4.1 文件格式偏好

| 优先级 | 格式 | 说明 |
|--------|------|------|
| ⭐ 首选 | `.md` | Markdown，Git 友好、diff 清晰、便于迭代 |
| 可选 | `.pdf` | 老师下发的课件、官方手册等无法转录的文件 |
| 可选 | 代码/项目文件夹 | 单片机/Linux 项目源码，需附带 README |

**请不要提交 Word (.doc/.docx) 文件。**

原因：
- Word 是二进制格式，Git 无法有效追踪变更，仓库体积会膨胀
- 每次修改都会产生一个几乎全新的文件，历史对比无意义
- Markdown 足够表达绝大多数技术文档需求

**如果你只有 Word 版本**：
1. 用 VS Code + Markdown 插件或 Typora 重新整理为 Markdown
2. 或者将 Word 内容粘贴到 Markdown 中，简单排版即可
3. 公式可用 LaTeX 语法（`$...$` 或 `$$...$$`），Markdown 渲染器均支持

### 4.2 文件存放位置

按仓库目录结构存放，详见 `README.md` 的"目录结构"部分。

基本原则：
- 放在正确的分类目录下
- 文件名使用中文或英文，避免特殊字符
- 同一主题的资料放在同一文件夹内

### 4.3 图片处理

Markdown 中引用图片：
```markdown
![说明文字](./images/示意图.png)
```

- 图片统一放在 `assets/images/` 或当前文档同目录的 `images/` 下
- 图片文件不要太大（建议单张 < 1MB）
- 优先使用 `.png` 或 `.jpg`，避免 `.bmp`

---

## 五、单次提交的最佳实践

1. **原子性**：一次提交只做一件事（如：新增一篇笔记，或修正一处错误）
2. **自包含**：提交的内容应该是完整的，不要提交半成品
3. **写好描述**：让其他人（包括未来的你自己）一眼明白这次提交做了什么
4. **先 pull 再 push**：推送前先 `git pull origin main`，减少冲突

---

## 六、常见问题

### Q1: 我修改了文件，但 push 被拒绝

A: 检查你是否在 `main` 分支上直接做了修改。如果是：
```bash
# 保存当前修改到临时分支
git checkout -b fix/临时分支
git add .
git commit -m "..."

# 然后按 squash merge 流程操作
git checkout main
git pull origin main
git merge --squash fix/临时分支
git commit -m "..."
git push origin main
```

### Q2: 合并时出现冲突

A: 冲突是因为你的修改和别人推送的内容有重叠。解决步骤：
```bash
# 冲突文件会标出来，手动编辑解决
# 解决后：
git add .
git commit -m "..."
git push origin main
```

### Q3: 我不小心提交了很大的文件

A: 不要慌，联系管理员帮忙从历史中移除（使用 `git filter-repo` 或 `git filter-branch`）。

---

## 七、资料质量建议

- **准确性**：技术内容尽量经过验证，不确定的标注"待确认"
- **可追溯**：引用外部资料时附带来源链接
- **可维护**：使用相对路径引用仓库内文件，避免绝对路径
- **版本标注**：对可能过时的内容（如特定年份的考题），在文件名或标题中标注年份

---

*最后更新：2026-05-07*
