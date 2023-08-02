import io.kotest.matchers.shouldBe
import org.junit.jupiter.api.Test

class BoardTest {
    @Test
    fun `can parse and print a board`() {
        val board = Board.parse(BOARD1_INPUT)

        board.dumpToString() shouldBe BOARD1_INPUT
    }

    @Test
    fun `impossible board is recognised as impossible`() {
        val board = Board.populate("""
             _12345678
             9________
             _________
             _________
             _________
             _________
             _________
             _________
             _________
        """.trimIndent())

        board.isImpossible() shouldBe true
    }

    @Test
    fun `can solve board1 (easy) in one iteration`() {
        val board = Board.populate(BOARD1_INPUT)

        val resultBoard = board.solve()

        resultBoard.isCompleted() shouldBe true
        resultBoard.dumpToString() shouldBe """
            534678912
            672195348
            198342567
            859761423
            426853791
            713924856
            961537284
            287419635
            345286179
        """.trimIndent()
    }

    @Test
    fun `can NOT solve board6 (hard) merely with repeated calls to solveOneIteration()`() {
        val board = Board.populate(BOARD6_INPUT)

        val bestWeCanDo = board.solveMultipleIterations()

        bestWeCanDo.isCompleted() shouldBe false
        bestWeCanDo.dumpToString() shouldBe """
            3__198_76
            9_17_53_4
            ____34_1_
            1__94__5_
            49__5_167
            52__71__3
            _3_417___
            2_53_97_1
            71_5___3_
        """.trimIndent()
    }

    @Test
    fun `we CAN solve board6 (hard) if make a guess and do a depth-first search of possible moves`() {
        val board = Board.populate(BOARD6_INPUT)

        val resultBoard = board.solve()

        resultBoard.isCompleted() shouldBe true
        resultBoard.dumpToString() shouldBe """
            342198576
            961725384
            857634912
            173946258
            498253167
            526871493
            639417825
            285369741
            714582639
        """.trimIndent()
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

        board.setSolvedCell(Position(1, 1), 7)

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
    fun `can solve a row where only one cell can be a particular value`() {
        val board = Board.populate(
            """
                ____45678
                1________
                _________
                _1_______
                _________
                _________
                __1______
                _________
                _________
            """.trimIndent()
        )

        val resultBoard = board.solveOneIteration()

        resultBoard.dumpToString() shouldBe """
                ___145678
                1________
                _________
                _1_______
                _________
                _________
                __1______
                _________
                _________
            """.trimIndent()
    }

    @Test
    fun `can solve a column where only one cell can be a particular value`() {
        val board = Board.populate(
            """
                __1______
                ___1_____
                ________1
                _________
                4________
                5________
                6________
                7________
                8________
            """.trimIndent()
        )

        val resultBoard = board.solveOneIteration()

        resultBoard.dumpToString() shouldBe """
                __1______
                ___1_____
                ________1
                1________
                4________
                5________
                6________
                7________
                8________
            """.trimIndent()
    }

    @Test
    fun `can solve a square where only one cell can be a particular value`() {
        val board = Board.populate(
            """
                ________1
                _____1___
                _________
                _1_______
                _________
                _________
                __1______
                _________
                _________
            """.trimIndent()
        )

         val resultBoard = board.solveOneIteration()

        resultBoard.dumpToString() shouldBe """
                ________1
                _____1___
                1________
                _1_______
                _________
                _________
                __1______
                _________
                _________
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

val BOARD6_INPUT = """
            _____8__6
            9_17_53_4
            _____4_1_
            1__94__5_
            49__5__67
            _2__71__3
            _3_4_____
            2_53_97_1
            7__5_____
        """.trimIndent()
