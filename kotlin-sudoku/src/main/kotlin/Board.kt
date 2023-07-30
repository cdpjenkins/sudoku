data class Board(val cells: MutableMap<Position, Cell>) {
    fun dump() {
        println(dumpToString())
    }

    fun dumpToString(): String {
        return (0..8).map { y: Int ->
            (0..8).map { x: Int ->
                cells[Position(x, y)]!!.dumpToString()
            }.joinToString("")
        }.joinToString("\n")
    }

    fun rows(): List<List<Cell>> {
        return rowPositions().map { rowPositions ->
            rowPositions.map { pos ->
                cells[pos]!!
            }
        }
    }

    private fun rowPositions(): List<List<Position>> {
        return (0..8).map {y ->
            row(y)
        }
    }

    private fun row(y: Int) =
        (0..8).map { x ->
            Position(x, y)
        }

    private fun column(x: Int): List<Position> =
        (0..8).map { y ->
            Position(x, y)
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
                            board.setCell(Position(x, y), value)
                        }
                    }
                }
            return board
        }
    }

    fun setCell(position: Position, value: Int) {
        cells[position] = Cell(setOf(value))

        row(position.y).minus(position).forEach {
            eliminatePossibility(it, value)
        }

        column(position.x).minus(position).forEach {
            eliminatePossibility(it, value)
        }
    }

    private fun eliminatePossibility(pos: Position, value: Int) {
        val oldCell = cells[pos]!!
        if (!oldCell.solved()) {
            val newCell = oldCell.eliminatePossibility(value)
            cells[pos] = newCell
            if (newCell.solved()) {
                setCell(pos, newCell.getSolvedValue())
            }
        }
    }
}

data class Cell(val possibilities: Set<Int>) {
    fun dumpToString(): String =
        if (possibilities.size == 1) {
            possibilities.first().toString()
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

