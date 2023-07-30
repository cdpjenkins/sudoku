data class Board(val cells: Map<Position, Cell>) {
    fun dump() {
        println(dumpToString())
    }

    fun dumpToString() =
        (0..8).map { y: Int ->
            (0..8).map { x: Int ->
                cells[Position(x, y)]!!.dumpToString()
            }.joinToString("")
        }.joinToString("\n")

    companion object {
        fun parse(contents: String): Board {
            val cells =
                contents.lines()
                    .withIndex().flatMap { (y, line) ->
                        line.withIndex().map { (x, ch) ->
                            Position(x, y) to Cell.parse(ch)
                        }
                    }.toMap()
            return Board(cells)
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

    companion object {
        fun parse(ch: Char) = Cell(ch.digitToIntOrNull()?.let { setOf(it) } ?: emptySet())
    }
}



data class Position(val x: Int, val y:Int) {

}

