data class Board(val cells: MutableMap<Position, Cell>) {
    fun solve(): Board {
        val newBoard = solveMultipleIterations()

        if (newBoard.isCompleted()) {
            return newBoard
        } else if (newBoard.isImpossible()) {
            return newBoard
        } else {
            return newBoard.depthFirstSearch()
        }
    }

    fun depthFirstSearch(): Board {
        val sortedPositions = this.cells.keys.sortedWith { lhs, rhs ->
            val cell = cellAt(lhs)
            cell.numPossibilitiesRemaining() - cellAt(rhs).numPossibilitiesRemaining()
        }

        val pos = sortedPositions
            .filter { cellAt(it).numPossibilitiesRemaining() > 1 }
            .first()
        val cell = cellAt(pos)

        val solns = cell.possibilitiesRemaining().map { value ->
            this.clone()
                .setSolvedCell(pos, value)
                .solve()
        }

        return solns.first { !it.isImpossible() }
    }

    fun solveOneIteration(): Board {
        val newBoard = this.clone().apply {
            (rows() + columns() + squares())
                .forEach { row ->
                    solveRegion(row)
                }
        }

        return newBoard
    }

    fun solveMultipleIterations(): Board {
        val boardSeq = generateSequence(this) {
            val nextBoard = it.solveOneIteration()
            if (nextBoard != it) nextBoard
            else null
        }

        return boardSeq.last()
    }

    fun isCompleted(): Boolean {
        return cells.all { (_, cell) -> cell.numPossibilitiesRemaining() == 1 }
    }

    fun isImpossible(): Boolean {
        return cells.any { (_, cell) -> cell.numPossibilitiesRemaining() == 0 }
    }

    private fun clone(): Board {
        return Board(cells.toMutableMap())
    }

    private fun solveRegion(region: List<Position>) {
        (1..9).forEach { value ->
            val cellsThatCouldBeThatValue = region.filter { value in cellAt(it).possibilitiesRemaining() }
            if (cellsThatCouldBeThatValue.size == 1) {
                setSolvedCell(cellsThatCouldBeThatValue.first(), value)
            }
        }
    }

    fun dump() {
        println(dumpToString())
    }

    fun dumpToString(): String {
        return (0..8).map { y: Int ->
            (0..8).map { x: Int ->
                cellAt(Position(x, y)).dumpToString()
            }.joinToString("")
        }.joinToString("\n")
    }

    private fun rows(): List<List<Position>> {
        return (0..8).map {y ->
            row(y)
        }
    }

    private fun row(y: Int) = (0..8).map { x -> Position(x, y) }

    private fun columns(): List<List<Position>> {
        return (0..8).map { x ->
            column(x)
        }
    }
    private fun column(x: Int): List<Position> = (0..8).map { y -> Position(x, y) }

    fun squares(): List<List<Position>> {
        return (0..8 step 3).flatMap { originY ->
            (0..8 step 3).map { originX ->
                (0..2).flatMap { y ->
                    (0..2).map { x ->
                        Position(x, y)
                    }
                }
            }
        }
    }

    private fun squareContaining(pos: Position): List<Position> {
        val xOrigin = pos.x - (pos.x % 3)
        val yOrigin = pos.y - (pos.y % 3)

        return (xOrigin..xOrigin+2).flatMap { x->
            (yOrigin..yOrigin+2).map { y ->
                Position(x, y)
            }
        }
    }

    companion object {
        fun parse(contents: String): Board {
            val cells =
                contents.lines()
                    .withIndex().flatMap { (y, line) ->
                        line.withIndex().map { (x, ch) ->
                            Position(x, y) to Cell.parse(ch)
                        }
                    }.toMap().toMutableMap()
            return Board(cells)
        }

        fun populate(contents: String): Board {
            val board =
                Board(
                    (0..8).flatMap { y ->
                        (0..8).map { x ->
                            Position(x, y) to Cell(Cell.ALL_POSSIBILITIES)
                        }
                    }.toMap().toMutableMap()
                )

            contents.lines()
                .withIndex().flatMap { (y, line) ->
                    line.withIndex().map { (x, ch) ->
                        val value = ch.digitToIntOrNull()

                        if (value != null) {
                            board.setSolvedCell(Position(x, y), value)
                        }
                    }
                }
            return board
        }
    }

    fun setSolvedCell(position: Position, value: Int): Board {
        cells[position] = Cell(setOf(value))

        val connectedCells = (row(position.y) + column(position.x) + squareContaining(position)).filter { it != position}
        connectedCells.forEach {
            eliminatePossibility(it, value)
        }

        return this
    }

    private fun eliminatePossibility(pos: Position, value: Int) {
        val oldCell = cellAt(pos)
        val newCell = oldCell.eliminatePossibility(value)
        cells[pos] = newCell
        if (!oldCell.solved() && newCell.solved()) {
            setSolvedCell(pos, newCell.getSolvedValue())
        }
    }

    private fun cellAt(lhs: Position) = this.cells[lhs]!!
}

data class Cell(private val possibilities: Set<Int>) {
    fun numPossibilitiesRemaining() = possibilities.size

    fun possibilitiesRemaining() = possibilities

    fun dumpToString(): String =
        if (numPossibilitiesRemaining() == 1) {
            possibilitiesRemaining().first().toString()
        } else {
            "_"
        }

    fun eliminatePossibility(value: Int): Cell {
        return if (value in possibilities) {
            Cell(possibilities - value)
        } else {
            this
        }
    }

    fun solved(): Boolean {
        return possibilities.size == 1
    }

    fun getSolvedValue(): Int {
        return if (possibilities.size == 1) {
            possibilities.first()
        } else {
            throw IllegalStateException("$this")
        }
    }

    companion object {
        val ALL_POSSIBILITIES = (1..9).toSet()

        fun parse(ch: Char) = Cell(ch.digitToIntOrNull()?.let { setOf(it) } ?: ALL_POSSIBILITIES)
    }
}

data class Position(val x: Int, val y:Int) {

}

