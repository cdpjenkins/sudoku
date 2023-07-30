import io.kotest.matchers.shouldBe
import org.junit.jupiter.api.Test

class BoardTest {
    @Test
    fun `can parse and print a board`() {
        val board = Board.parse(BOARD1_INPUT)

        board.dumpToString() shouldBe BOARD1_INPUT
    }

    @Test
    fun `can set a single cell`() {
        val board = Board.populate(
            """
                _________
                _________
                _________
                _________
                _________
                _________
                _________
                _________
                _________
            """.trimIndent()
        )

        board.setCell(Position(1, 1), 7)

        board.dumpToString() shouldBe """
                _________
                _7_______
                _________
                _________
                _________
                _________
                _________
                _________
                _________
            """.trimIndent()
    }

    @Test
    fun `can solve a row`() {
        val board = Board.populate(
            """
                12345678_
                _________
                _________
                _________
                _________
                _________
                _________
                _________
                _________
            """.trimIndent()
        )

        board.dumpToString() shouldBe """
                123456789
                _________
                _________
                _________
                _________
                _________
                _________
                _________
                _________
            """.trimIndent()
    }

    @Test
    fun `can solve a region`() {
        val board = Board.populate(
            """
                123______
                456______
                78_______
                _________
                _________
                _________
                _________
                _________
                _________
            """.trimIndent()
        )

        board.dumpToString() shouldBe """
                123______
                456______
                789______
                _________
                _________
                _________
                _________
                _________
                _________
            """.trimIndent()
    }


    @Test
    fun `can solve a column`() {
        val board = Board.populate(
            """
                ________1
                ________2
                ________3
                ________4
                ________5
                ________6
                ________7
                ________8
                _________
            """.trimIndent()
        )

        board.dumpToString() shouldBe """
                ________1
                ________2
                ________3
                ________4
                ________5
                ________6
                ________7
                ________8
                ________9
            """.trimIndent()
    }

    @Test
    fun `solving one cell propagates to other connected cells`() {
        val board = Board.populate(
            """
                ________9
                ________8
                ________7
                ________6
                ________5
                ________4
                ________3
                ________2
                _2345678_
            """.trimIndent()
        )

        board.dumpToString() shouldBe """
                ________9
                ________8
                ________7
                ________6
                ________5
                ________4
                ________3
                ________2
                923456781
            """.trimIndent()
    }


}

val BOARD1_INPUT = """
            53__7____
            6__195___
            _98____6_
            8___6___3
            4__8_3__1
            7___2___6
            _6____28_
            ___419__5
            ____8__79
        """.trimIndent()
