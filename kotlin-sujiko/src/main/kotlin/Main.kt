data class SujikoBoard(
    val totals: List<Int>,
    val squares: MutableList<Set<Int>>
) {
    fun isValid() = squares.none { it.isEmpty() }

    fun isFilledIn() = squares.all { it.size == 1 }
    fun isComplete(): Boolean {
        if (!isFilledIn()) {
            return false
        }

        if (squares[0].first() + squares[1].first() +
            squares[3].first() + squares[4].first() != totals[0]) {
            return false
        }

        if (squares[1].first() + squares[2].first() +
            squares[4].first() + squares[5].first() != totals[1]) {
            return false
        }

        if (squares[3].first() + squares[4].first() +
            squares[6].first() + squares[7].first() != totals[2]) {
            return false
        }

        if (squares[4].first() + squares[5].first() +
            squares[7].first() + squares[8].first() != totals[3]) {
            return false
        }

        return true
    }

    fun solve(): SujikoBoard? {
        if (isFilledIn() && isComplete()) {
            return this
        } else if (!isValid()) {
            return null
        }

        val indexWhereWeWillGuess = (0..8).sortedWith { lhs, rhs ->
            squares[lhs].size - squares[rhs].size
        }
            .filter { squares[it].size > 1 }
            .firstOrNull()

        if (indexWhereWeWillGuess == null) {
            return null
        }

        val possibilities = squares[indexWhereWeWillGuess]

        val map = possibilities.map { value ->
            val board = this.clone()
            board.setSquare(indexWhereWeWillGuess, value)
            board.solve()
        }.filterNotNull()
            .filter{ it.isValid() }

        return map.firstOrNull()
    }

    private fun clone(): SujikoBoard {
        return SujikoBoard(totals.toList(), squares.toMutableList())
    }

    private fun setSquare(index: Int, digit: Int) {
        squares[index] = setOf(digit)

        for (i in (0..8)) {
            if (i != index) {
                squares[i] = squares[i].minus(digit)
            }
        }
    }

    private fun setSquare(x: Int, y: Int, digit: Int) {
        val indexToSet = y*3 + x

        setSquare(indexToSet, digit)
    }

    fun print() {
        for (y in 0..2) {
            for (x in 0..2) {
                print(squares[y*3 + x].first())
            }
            println()
        }
        println()
    }

    companion object {
        fun parse(input: String): SujikoBoard {
            val lines = input.lines()

            val totalsLine = lines.first()
            val totals = totalsLine.split(",")
                .map { it.toInt() }

            val squares: MutableList<Set<Int>> = MutableList(9) {
                setOf(1, 2, 3, 4, 5, 6, 7, 8, 9)
            }

            val board = SujikoBoard(totals, squares)

            val squaresLines = lines.drop(1)
            squaresLines.withIndex().forEach { (y, line) ->
                line.withIndex().forEach { (x, c) ->
                    val digit = c.digitToIntOrNull()
                    if (digit != null) {
                        board.setSquare(x, y, digit)
                    }
                }
            }

            return board
        }
    }
}

fun main(args: Array<String>) {
    val input = """
        17,17,17,17
        94_
        ___
        ___
    """.trimIndent()

    val board = SujikoBoard.parse(input)

    val solved = board.solve()

    println(solved)

    solved?.print()

}
