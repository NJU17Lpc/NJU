package edLineEditor;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.*;

import static org.junit.Assert.assertEquals;

public class EDLineEditorTest {

    InputStream in = null;
    PrintStream out = null;

    InputStream inputStream = null;
    ByteArrayOutputStream outputStream = null;

    String lineBreak = null;

    @Before
    public void setUp() {
        in = System.in;
        out = System.out;
        outputStream = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outputStream));

        lineBreak = System.getProperty("line.separator");
    }

    @After
    public void tearDown() {
        System.setIn(in);
        System.setOut(out);
    }

    /**
     * command p with default address
     * command q
     */
    @Test
    public void test001() {
        String testFile = "test001";
        String content = "cn" + lineBreak + "test" + lineBreak + "software" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test001" + lineBreak,
                "p" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "software" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command p . Your output does not match!", arrayToString(outputs), outputStream.toString());

        String file = "test001";
        String fileContent = "cn" + lineBreak +
                "test" + lineBreak +
                "software" + lineBreak;

        assertFile(file, fileContent, "Test command p .You should not modify the file test001 ed reads.");
    }

    /**
     * command p with ',' address
     */
    @Test
    public void test002() {
        String testFile = "test002";
        String content = "cn" + lineBreak + "test" + lineBreak + "software" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test002" + lineBreak,
                ",p" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "cn" + lineBreak + "test" + lineBreak + "software" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command p with , . Your output does not match!", arrayToString(outputs), outputStream.toString());
    }


    /**
     * command p with related address
     */
    @Test
    public void test003() {
        String testFile = "test003";
        String content = "java" + lineBreak + "1" + lineBreak + "2" + lineBreak + "3" + lineBreak + "end" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test003" + lineBreak,
                "3p" + lineBreak,
                "+2p" + lineBreak,
                "-4p" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "2" + lineBreak,
                "end" + lineBreak,
                "java" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command p with +n???-n address . Your output does not match!", arrayToString(outputs), outputStream.toString());
    }

    /**
     * command p with range address
     */
    @Test
    public void test004() {
        String testFile = "test004";
        String content = "java" + lineBreak + "one" + lineBreak + "two" + lineBreak + "three" + lineBreak + "end" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test004" + lineBreak,
                "2,4p" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "one" + lineBreak + "two" + lineBreak + "three" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command p with m,n . Your output does not match!", arrayToString(outputs), outputStream.toString());
    }

    /**
     * command p with '$' address
     */
    @Test
    public void test005() {
        String testFile = "test005";
        String content = "5" + lineBreak + "one" + lineBreak + "two" + lineBreak + "three" + lineBreak + "end" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test005" + lineBreak,
                "$p" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "end" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command p with $ . Your output does not match!", arrayToString(outputs), outputStream.toString());
    }

    /**
     * command p with ';' address
     */
    @Test
    public void test006() {
        String testFile = "test006";
        String content = "6" + lineBreak + "one" + lineBreak + "two" + lineBreak + "three" + lineBreak + "end" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test006" + lineBreak,
                "2p" + lineBreak,
                ";p" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "one" + lineBreak,
                "one" + lineBreak + "two" + lineBreak + "three" + lineBreak + "end" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command p with ; . Your output does not match!", arrayToString(outputs), outputStream.toString());
    }

    /**
     * command p with '/str/' address
     */
    @Test
    public void test007() {
        String testFile = "test007";
        String content = "test" + lineBreak + "1a" + lineBreak + "2b" + lineBreak + "3a" + lineBreak + "testb end" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test007" + lineBreak,
                "3p" + lineBreak,
                "/a/p" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "2b" + lineBreak,
                "3a" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command p with /str/ . Your output does not match!", arrayToString(outputs), outputStream.toString());
    }

    /**
     * command p with '?str?' address
     */
    @Test
    public void test008() {
        String testFile = "test008";
        String content = "test" + lineBreak + "1a" + lineBreak + "2b" + lineBreak + "3a" + lineBreak + "testb end" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test008" + lineBreak,
                "3p" + lineBreak,
                "?a?p" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "2b" + lineBreak,
                "1a" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command p with ?str? . Your output does not match!", arrayToString(outputs), outputStream.toString());
    }

    /**
     * command a with default address
     * command w with file
     */
    @Test
    public void test009() {
        String[] inputs = {
                "ed" + lineBreak,
                "a" + lineBreak,
                "cn" + lineBreak,
                "test" + lineBreak,
                "software" + lineBreak,
                "." + lineBreak,
                "w test009" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {};

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command a .You should not give any output!", arrayToString(outputs), outputStream.toString());

        String file = "test009";
        String fileContent = "cn" + lineBreak + "test" + lineBreak + "software" + lineBreak;

        assertFile(file, fileContent, "Test command a . The file you save: test009's content does not match.");
    }

    /**
     * command a with address
     * command w
     */
    @Test
    public void test010() {
        String testFile = "test010";
        String content = "5" + lineBreak + "java" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test010" + lineBreak,
                "1a" + lineBreak,
                "test010" + lineBreak,
                "3" + lineBreak,
                "." + lineBreak,
                "w" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {};

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command a with address . You should not give any output!", arrayToString(outputs), outputStream.toString());

        String file = "test010";
        String fileContent = "5" + lineBreak +
                "test010" + lineBreak +
                "3" + lineBreak +
                "java" + lineBreak;

        assertFile(file, fileContent, "Test command a with address . The file you save: test010's content does not match.");
    }

    /**
     * command a with related address
     * command w
     */
    @Test
    public void test011() {
        String testFile = "test011";
        String content = "10" + lineBreak + "java" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test011" + lineBreak,
                "-1a" + lineBreak,
                "test011" + lineBreak,
                "." + lineBreak,
                "w" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {};

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command a with +n???-n address . You should not give any output!", arrayToString(outputs), outputStream.toString());

        String file = "test011";
        String fileContent = "10" + lineBreak +
                "test011" + lineBreak +
                "java" + lineBreak;

        assertFile(file, fileContent, "Test command a with +n???-n address . The file you save: test011's content does not match.");
    }

    /**
     * command i with default address
     * command p
     * command w with file
     */
    @Test
    public void test012() {
        String testFile = "test012";
        String content = "software" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test012" + lineBreak,
                "i" + lineBreak,
                "test012" + lineBreak,
                "haha" + lineBreak,
                "." + lineBreak,
                ",p" + lineBreak,
                "w test012_2" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "test012" + lineBreak + "haha" + lineBreak + "software" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command i . Your output does not match!", arrayToString(outputs), outputStream.toString());

        String file1 = "test012";
        String fileContent1 = "software" + lineBreak;

        assertFile(file1, fileContent1, "Test command w file . You should not modify the file test012 ed reads.");

        String file2 = "test012_2";
        String fileContent2 = "test012" + lineBreak +
                "haha" + lineBreak +
                "software" + lineBreak;

        assertFile(file2, fileContent2, "Test command w file . The file you save: test012_2's content does not match.");
    }

    /**
     * command i with address
     * command w
     */
    @Test
    public void test013() {
        String testFile = "test013";
        String content = "test" + lineBreak + "1a" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test013" + lineBreak,
                "1i" + lineBreak,
                "test013" + lineBreak,
                "." + lineBreak,
                ",p" + lineBreak,
                "w" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "test013" + lineBreak + "test" + lineBreak + "1a" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

        assertEquals("Test command i with n address . Your output does not match!", arrayToString(outputs), outputStream.toString());

        String file2 = "test013";
        String fileContent2 = "test013" + lineBreak +
                "test" + lineBreak +
                "1a" + lineBreak;

        assertFile(file2, fileContent2, "Test command i with n address . The file you save: test013's content does not match.");
    }

    /**
     * command i with related address
     * command w
     */
    @Test
    public void test014() {
        String testFile = "test014";
        String content = "test" + lineBreak + "1a" + lineBreak + "2b" + lineBreak + "3c" + lineBreak;
        createFile(testFile, content);

        String[] inputs = {
                "ed test014" + lineBreak,
                "1p" + lineBreak,
                "+2i" + lineBreak,
                "test014" + lineBreak,
                "." + lineBreak,
                "w" + lineBreak,
                "q" + lineBreak
        };

        String[] outputs = {
                "test" + lineBreak
        };

        inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
        System.setIn(inputStream);

        EDLineEditor.main(null);

		assertEquals("Test command p before i with +n???-n address . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test014";
		String fileContent = "test" + lineBreak + 
				"1a" + lineBreak + 
				"test014" + lineBreak + 
				"2b" + lineBreak + 
				"3c" + lineBreak;
		
		assertFile(file, fileContent, "Test command i with +n???-n address . The file you save: test014's content does not match.");
	}
	
	/**
	 * command c with default address
	 */
	@Test
	public void test015() {
		String testFile = "test015";
		String content = "Good job!" + lineBreak + "haha" + lineBreak + "software" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test015" + lineBreak,
				"c" + lineBreak,
				"666" + lineBreak,
				"java" + lineBreak,
				"." + lineBreak,
				",p" + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"Good job!" + lineBreak + "haha" + lineBreak + "666" + lineBreak + "java" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command c . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test015";
		String fileContent = "Good job!" + lineBreak + 
				"haha" + lineBreak + 
				"666" + lineBreak + 
				"java" + lineBreak;
		
		assertFile(file, fileContent, "Test command c . The file you save: test015's content does not match.");
	}
	
	/**
	 * command c with range address
	 */
	@Test
	public void test016() {
		String testFile = "test016";
		String content = "Good job!" + lineBreak + "haha" + lineBreak + "software" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test016" + lineBreak,
				"1,2c" + lineBreak,
				"666" + lineBreak,
				"." + lineBreak,
				",p" + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"666" + lineBreak + "software" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command c with x,x address . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test016";
		String fileContent = "666" + lineBreak + 
				"software" + lineBreak;
		
		assertFile(file, fileContent, "Test command c with x,x address . The file you save: test016's content does not match.");
	}
	
	/**
	 * command d with default address
	 */
	@Test
	public void test017() {
		String testFile = "test017";
		String content = "cn" + lineBreak + "test017" + lineBreak + "software" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test017" + lineBreak,
				"d" + lineBreak,
				",p" + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"cn" + lineBreak + "test017" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command d . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test017";
		String fileContent = "cn" + lineBreak + 
				"test017" + lineBreak;
		
		assertFile(file, fileContent, "Test command d . The file you save: test017's content does not match.");
	}

	/**
	 * command d with address
	 */
	@Test
	public void test018() {
		String testFile = "test018";
		String content = "com" + lineBreak + "test" + lineBreak + "soft" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test018" + lineBreak,
				"2d" + lineBreak,
				",p" + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"com" + lineBreak + "soft" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command d with address . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test018";
		String fileContent = "com" + lineBreak + 
				"soft" + lineBreak;
		
		assertFile(file, fileContent, "Test command d with address . The file you save: test018's content does not match.");
	}

	/**
	 * command d with range address
	 */
	@Test
	public void test019() {
		String testFile = "test019";
		String content = "fighting" + lineBreak + "test019" + lineBreak + "gan" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test019" + lineBreak,
				"2,3d" + lineBreak,
				",p" + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"fighting" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command d with m,n address . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test019";
		String fileContent = "fighting" + lineBreak;
		
		assertFile(file, fileContent, "Test command d with m,n address . The file you save: test019's content does not match.");
	}

	/**
	 * command =
	 */
	@Test
	public void test020() {
		String[] inputs = {
				"ed" + lineBreak,
				"i" + lineBreak,
				"1" + lineBreak,
				"2" + lineBreak,
				"3" + lineBreak,
				",p" + lineBreak,
				"." + lineBreak,
				"=" + lineBreak,
				"w test020" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"4" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command = with default address . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test020";
		String fileContent = "1" + lineBreak + 
				"2" + lineBreak + 
				"3" + lineBreak + 
				",p" + lineBreak;
		
		assertFile(file, fileContent, "Test command = with default address . The file you save: test020's content does not match.");
	}
	
	/**
	 * command = with address
	 */
	@Test
	public void test021() {
		String testFile = "test021";
		String content = "fighting" + lineBreak + "test021" + lineBreak + "3c" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test021" + lineBreak,
				".=" + lineBreak,
				"2=" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"3" + lineBreak,
				"2" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command = with .???n address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command = with related address
	 */
	@Test
	public void test022() {
		String testFile = "test022";
		String content = "1a" + lineBreak + "test2b" + lineBreak + "3c" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test022" + lineBreak,
				"-2=" + lineBreak,
				".=" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"1" + lineBreak,
				"3" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command = with +n???. address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command c with , address
	 */
	@Test
	public void test023() {
		String testFile = "test023";
		String content = "1a" + lineBreak + "test2b" + lineBreak + "3c" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test023" + lineBreak,
				",c" + lineBreak,
				"replace all" + lineBreak,
				"." + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command c with , address . You should not give any output!", arrayToString(outputs), outputStream.toString());
		
		String file = "test023";
		String fileContent = "replace all" + lineBreak;
		
		assertFile(file, fileContent, "Test command c with , address . The file you save: test023's content does not match.");
	
	}
	
	/**
	 * command z
	 */
	@Test
	public void test024() {
		String testFile = "test024";
		String content = "zn" + lineBreak + "scala" + lineBreak + "python" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test024" + lineBreak,
				"1z2" + lineBreak,
				"2z1" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"zn" + lineBreak + "scala" + lineBreak + "python" + lineBreak,
				"scala" + lineBreak + "python" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command z . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command z with default address
	 */
	@Test
	public void test025() {
		String testFile = "test025";
		String content = "zn" + lineBreak + "2a" + lineBreak + "5A" + lineBreak + "win10" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test025" + lineBreak,
				"1p" + lineBreak,
				"z2" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"zn" + lineBreak,
				"2a" + lineBreak + "5A" + lineBreak + "win10" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command z with default address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command z with -n address and no param
	 */
	@Test
	public void test026() {
		String testFile = "test026";
		String content = "zn" + lineBreak + "3a" + lineBreak + "5A" + lineBreak + "win10" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test026" + lineBreak,
				"-2z" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"3a" + lineBreak + "5A" + lineBreak + "win10" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command z with -n address and no param . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}

	/**
	 * command z with param referring to over lines
	 */
	@Test
	public void test027() {
		String testFile = "test027";
		String content = "zn" + lineBreak + "4a" + lineBreak + "5A" + lineBreak + "win10" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test027" + lineBreak,
				"3z3" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"5A" + lineBreak + "win10" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command z with param referring to over lines . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command Q after d with ;
	 */
	@Test
	public void test028() {
		String testFile = "test028";
		String content = "a" + lineBreak + "test" + lineBreak + "city" + lineBreak + "shanghai" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test028" + lineBreak,
				";d" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"a" + lineBreak + "test" + lineBreak + "city" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command d with ; .Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test028";
		String fileContent = "a" + lineBreak + 
				"test" + lineBreak + 
				"city" + lineBreak + 
				"shanghai" + lineBreak;
		
		assertFile(file, fileContent, "Test command Q . You should not change file test028's content ed reads.");
	
	}
	
	/**
	 * command q
	 */
	@Test
	public void test029() {
		String testFile = "test029";
		String content = "029" + lineBreak + "java" + lineBreak + "se" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test029" + lineBreak,
				"2d" + lineBreak,
				"q" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command q without saving . Your output does not match!", arrayToString(outputs), outputStream.toString());

		String file = "test029";
		String fileContent = "029" + lineBreak + 
				"java" + lineBreak + 
				"se" + lineBreak;
		
		assertFile(file, fileContent, "Test command q without saving . You should not modify the file test029 ed reads.");
		
	}
	
	/**
	 * command W
	 */
	@Test
	public void test030() {
		String testFile = "test030";
		String content = "1a" + lineBreak + "test" + lineBreak + "3c" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test030" + lineBreak,
				"2p" + lineBreak,
				";c" + lineBreak,
				"replace some" + lineBreak,
				"." + lineBreak,
				"W" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"test" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with n address . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test030";
		String fileContent = "1a" + lineBreak + 
				"test" + lineBreak + 
				"3c" + lineBreak + 
				"1a" + lineBreak + 
				"replace some" + lineBreak;
		
		assertFile(file, fileContent, "Test command W and c with ; address . The file you save: test030's content does not match.");
	
	}
	
	/**
	 * command w with address
	 */
	@Test
	public void test031() {
		String testFile = "test031";
		String content = "031a" + lineBreak + "test" + lineBreak + "5G" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test031" + lineBreak,
				"1,2w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command w with m,n address . You should not give any output!", arrayToString(outputs), outputStream.toString());
		
		String file = "test031";
		String fileContent = "031a" + lineBreak + 
				"test" + lineBreak;
		
		assertFile(file, fileContent, "Test command w with m,n address . The file you save: test031's content does not match.");
	
	}
	
	/**
	 * command W with address
	 */
	@Test
	public void test032() {
		String testFile = "test032";
		String content = "032a" + lineBreak + "test" + lineBreak + "awesome" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test032" + lineBreak,
				"3W" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"032a" + lineBreak + "test" + lineBreak + "awesome" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with , address after W . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test032";
		String fileContent = "032a" + lineBreak + 
				"test" + lineBreak + 
				"awesome" + lineBreak + 
				"awesome" + lineBreak;
		
		assertFile(file, fileContent, "Test command W with n address . The file you save: test032's content does not match.");
	
	}
	
	/**
	 * command f
	 */
	@Test
	public void test033() {
		String testFile = "test033";
		String content = "033a" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test033" + lineBreak,
				"f" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"test033" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command f . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command f with param
	 */
	@Test
	public void test034() {
		String testFile = "test034";
		String content = "034w" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test034" + lineBreak,
				"f test034_2" + lineBreak,
				"f" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"test034_2" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command f and showing file name set . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command w after command f setting file name
	 */
	@Test
	public void test035() {
		String testFile = "test035";
		String content = "035=17+018" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test035" + lineBreak,
				"f test035_2" + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command w after command f setting file name . You should not give any output!", arrayToString(outputs), outputStream.toString());

		String file = "test035";
		String fileContent = "035=17+018" + lineBreak;
		
		assertFile(file, fileContent, "Test command w after command f setting file name . You should not modify the file test035's content ed reads.");

		String file2 = "test035_2";
		String fileContent2 = "035=17+018" + lineBreak;
		
		assertFile(file2, fileContent2, "Test command w after command f setting file name . The file you save: test035_2's content does not match.");
	}
	
	/**
	 * command m with default address
	 */
	@Test
	public void test036() {
		String testFile = "test036";
		String content = "036a" + lineBreak + "test" + lineBreak + "awesome*3" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test036" + lineBreak,
				"m" + lineBreak,
				".p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"awesome*3" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with . address after m with default address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command m with single source address
	 */
	@Test
	public void test037() {
		String testFile = "test037";
		String content = "037c" + lineBreak + "test%" + lineBreak + "awesome*XPhone" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test037" + lineBreak,
				"1m" + lineBreak,
				".p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"037c" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with . address after m with single source address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command m with range source address
	 */
	@Test
	public void test038() {
		String testFile = "test038";
		String content = "038c" + lineBreak + "test@" + lineBreak + "nju" + lineBreak + "ed" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test038" + lineBreak,
				"1,2m" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"nju" + lineBreak + "ed" + lineBreak + "038c" + lineBreak + "test@" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with , address after m with range source address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command m with source and target address
	 */
	@Test
	public void test039() {
		String testFile = "test039";
		String content = "nju" + lineBreak + "ed" + lineBreak + "039c" + lineBreak + "test@" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test039" + lineBreak,
				"1,2m3" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"039c" + lineBreak + "nju" + lineBreak + "ed" + lineBreak + "test@" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with , address after m with source and target address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}

	/**
	 * command t with default address
	 */
	@Test
	public void test040() {
		String testFile = "test040";
		String content = "040t" + lineBreak + "test" + lineBreak + "java" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test040" + lineBreak,
				"t" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"040t" + lineBreak + "test" + lineBreak + "java" + lineBreak + "java" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with . address after t with default address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command t with single source address
	 */
	@Test
	public void test041() {
		String testFile = "test041";
		String content = "041t" + lineBreak + "university" + lineBreak + "edu" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test041" + lineBreak,
				"2t" + lineBreak,
				".p" + lineBreak,
				".=" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"university" + lineBreak,
				"4" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p and = with . address after t with single source address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command t with range source address
	 */
	@Test
	public void test042() {
		String testFile = "test042";
		String content = "042t" + lineBreak + "2w" + lineBreak + "3e" + lineBreak + "4r" + lineBreak + "5t" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test042" + lineBreak,
				"-2,3t" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"042t" + lineBreak + "2w" + lineBreak + "3e" + lineBreak + "4r" + lineBreak + "5t" + lineBreak + "3e" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with , address after t with range source address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command t with source and target address
	 */
	@Test
	public void test043() {
		String testFile = "test043";
		String content = "043t" + lineBreak + "ed" + lineBreak + "java" + lineBreak + "5njuer" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test043" + lineBreak,
				"4t1" + lineBreak,
				".=" + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"2" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command = with . address after t with source and target address . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test043";
		String fileContent = "043t" + lineBreak + 
				"5njuer" + lineBreak + 
				"ed" + lineBreak + 
				"java" + lineBreak + 
				"5njuer" + lineBreak;
		
		assertFile(file, fileContent, "Test command t with source and target address and w . The file you save: test043's content does not match.");
	}

	/**
	 * command j with default address
	 */
	@Test
	public void test044() {
		String testFile = "test044";
		String content = "044j" + lineBreak + "test" + lineBreak + "java" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test044" + lineBreak,
				"2p" + lineBreak,
				"j" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"test" + lineBreak,
				"044j" + lineBreak + "testjava" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command j with default address after p with n address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command j with range address
	 */
	@Test
	public void test045() {
		String testFile = "test045";
		String content = "045j" + lineBreak + "2w" + lineBreak + "3e" + lineBreak + "4r" + lineBreak + "5t" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test045" + lineBreak,
				"-2,$j" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"045j" + lineBreak + "2w" + lineBreak + "3e4r5t" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with , address after j with range address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command j with , address
	 */
	@Test
	public void test046() {
		String testFile = "test046";
		String content = "046j" + lineBreak + "1q" + lineBreak + "2s" + lineBreak + "3c" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test046" + lineBreak,
				",j" + lineBreak,
				"1p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"046j1q2s3c" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with n address after j with , address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with default address and /str1/str2/
	 */
	@Test
	public void test047() {
		String testFile = "test047";
		String content = "047s" + lineBreak + "1q2b3q4d5qwt" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test047" + lineBreak,
				"s/q/rep/" + lineBreak,
				"p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"1rep2b3q4d5qwt" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p after s with default address and param /str1/str2/ . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with range address and /str1/str2/count
	 */
	@Test
	public void test048() {
		String testFile = "test048";
		String content = "048s" + lineBreak + "1zq2b3q4d5qwt" + lineBreak + "1w2c3q4d5qwt" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test048" + lineBreak,
				"2,3s/q/rep/2" + lineBreak,
				"2,3p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"1zq2b3rep4d5qwt" + lineBreak + "1w2c3q4d5repwt" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p after s with range address and param /str1/str2/count . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command k
	 */
	@Test
	public void test049() {
		String testFile = "test049";
		String content = "049k" + lineBreak + "cctv7" + lineBreak + "cctv2" + lineBreak + "cctv5" + lineBreak + "cctv4" + lineBreak + 
				"cctv3" + lineBreak + "cctv6" + lineBreak + "cctv1" + lineBreak + "cctv8" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test049" + lineBreak,
				"?cctv5?kf" + lineBreak,
				"'fp" + lineBreak,
				"'f=" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"cctv5" + lineBreak,
				"4" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p and = with mark after k . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command u
	 */
	@Test
	public void test050() {
		String testFile = "test050";
		String content = "050u" + lineBreak + "student1" + lineBreak + "student3" + lineBreak + "student2" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test050" + lineBreak,
				"a" + lineBreak,
				"student4" + lineBreak,
				"." + lineBreak,"w abcdefgh" + lineBreak,
				"3m4" + lineBreak,

				",p" + lineBreak,
				"u" + lineBreak,
				",p" + lineBreak,
				"u" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"050u" + lineBreak + "student1" + lineBreak + "student2" + lineBreak + "student3" + lineBreak + "student4" + lineBreak,
				"050u" + lineBreak + "student1" + lineBreak + "student3" + lineBreak + "student2" + lineBreak + "student4" + lineBreak,
				"050u" + lineBreak + "student1" + lineBreak + "student3" + lineBreak + "student2" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command u (showing content with ,p) two times after command m and command a . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with default address and /str1/str2/g
	 */
	@Test
	public void test051() {
		String testFile = "test051";
		String content = "051s" + lineBreak + "1q2b3q4d5qwt" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test051" + lineBreak,
				"s/q/rep/g" + lineBreak,
				"p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"1rep2b3rep4d5repwt" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p after s with default address and param /str1/str2/g . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with range address and /str1/str2/count
	 * all lines match
	 * command W with range address and file_2 exist
	 */
	@Test
	public void test052() {
		String testFile = "test052";
		String content = "//052s" + lineBreak + "int in = (int) java.lang.Math.sqrt(9);" + lineBreak + "System.out.println(\"result = \"+in);" + lineBreak;
		createFile(testFile, content);
		
		String testFile_2 = "test052_2";
		String content_2 = "//052_2s" + lineBreak;
		createFile(testFile_2, content_2);
		
		String[] inputs = {
				"ed test052" + lineBreak,
				".-1,.s/in/res/2" + lineBreak,
				".-1,$p" + lineBreak,
				"2,3W test052_2" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"int res = (int) java.lang.Math.sqrt(9);" + lineBreak + "System.out.println(\"result = \"+res);" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p after s with range address and param /str1/str2/count . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test052_2";
		String fileContent = "//052_2s" + lineBreak + 
				"int res = (int) java.lang.Math.sqrt(9);" + lineBreak + 
				"System.out.println(\"result = \"+res);" + lineBreak;
		
		assertFile(file, fileContent, "Test command W after s .The file you save: test052_2's content does not match.");
	}
	
	/**
	 * command s with range address and /str1/str2/count
	 * part of lines match
	 */
	@Test
	public void test053() {
		String testFile = "test053";
		String content = "//053s" + lineBreak + 
				"String hello = \"hello, world.hello, China.hello, nju.\";" + lineBreak + 
				"String[] hellos = hello.split(\".\")" + lineBreak + 
				"System.out.println(hellos[hellos.length-1]);" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test053" + lineBreak,
				"2,4s/hello/welcome/4" + lineBreak,
				"2,3p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"String hello = \"hello, world.hello, China.welcome, nju.\";" + lineBreak + 
				"String[] hellos = hello.split(\".\")" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p after s with range address and param /str1/str2/count (part of lines match) . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
	}
	
	/**
	 * command s with range address and /str1/str2/count
	 * no line matches
	 */
	@Test
	public void test054() {
		String testFile = "test054";
		String content = "//054s" + lineBreak + 
				"int a=2,b=3;" + lineBreak + 
				"int temp = a;" + lineBreak + 
				"a = b;" + lineBreak + 
				"b = temp;" + lineBreak + 
				"System.out.println(\"a=\"+a+\",b=\"+b);" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test054" + lineBreak,
				",s/template/temp/1" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command s with range address and param /str1/str2/count (no line matches) . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with range address and /str1/str2/g
	 * part of lines match
	 * ???????????????linux???ed???????????????????????????s???????????????????????????????????????????????????????????????ed??????????????????????????????????????????
	 */
	@Test
	public void test055() {
		String testFile = "test055";
		String content = "//055s" + lineBreak + 
				"1test2for3print4test wwtest;" + lineBreak + 
				"day 3test:dinner lunch breakfast" + lineBreak + 
				"pet:cat2dog3fish4monkey" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test055" + lineBreak,
				",s/test/welcome/g" + lineBreak,
				".=" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"3" + lineBreak,
				"//055s" + lineBreak + 
				"1welcome2for3print4welcome wwwelcome;" + lineBreak + 
				"day 3welcome:dinner lunch breakfast" + lineBreak + 
				"pet:cat2dog3fish4monkey" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command s with range address and param /str1/str2/g (part of lines match) . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}

	/**
	 * command s with range address composed of /str/ or ?str? address
	 */
	@Test
	public void test056() {
		String testFile = "test056";
		String content = "//056s" + lineBreak + 
				"breakfast:bre,soybrean milk,meat dumpling,bread" + lineBreak + 
				"lunch:bread,rice,vegetable,meat,so on,brea" + lineBreak + 
				"supper:chilly pot,soup" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test056" + lineBreak,
				"/so/,?illy?-1s/brea/bea/2" + lineBreak,
				".-1,$p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"breakfast:bre,soybean milk,meat dumpling,bread" + lineBreak + 
				"lunch:bread,rice,vegetable,meat,so on,bea" + lineBreak + 
				"supper:chilly pot,soup" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Showing content with command p after command s with /str/,?str? address and param /str1/str2/n . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with no param
	 * no command s ahead
	 */
	@Test
	public void test057() {
		String testFile = "test057";
		String content = "//057s" + lineBreak + 
				"test" + lineBreak + 
				"dinner lunch breakfast" + lineBreak + 
				"pet" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test057" + lineBreak,
				"s" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command s with no param and no command s ahead . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with /str/ or ?str? address
	 */
	@Test
	public void test058() {
		String testFile = "test058";
		String content = "//058s" + lineBreak + 
				"todo:take online course" + lineBreak + 
				"completed:programming" + lineBreak + 
				"todo:surf the Internet" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test058" + lineBreak,
				"/todo/s/todo/completed/" + lineBreak,
				";p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"completed:take online course" + lineBreak + 
				"completed:programming" + lineBreak + 
				"todo:surf the Internet" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command ;p after command s with /str/ or ?str? address and param /str1/str2/ . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with ?todo? address and no param
	 * There is command s ahead.
	 */
	@Test
	public void test059() {
		String testFile = "test059";
		String content = "//059s" + lineBreak + 
				"todo:take online course" + lineBreak + 
				"completed:programming" + lineBreak + 
				"todo:surf the Internet" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test059" + lineBreak,
				"?todo?s/todo/completed/" + lineBreak,
				".p" + lineBreak,
				"?todo?s" + lineBreak,
				".p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"completed:take online course" + lineBreak, 
				"completed:surf the Internet" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command s with no param and there is a command s ahead . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with /todo/ address and no param
	 * There is command s ahead but no line match for current s.
	 */
	@Test
	public void test060() {
		String testFile = "test060";
		String content = "//060s" + lineBreak + 
				"completed:programming" + lineBreak + 
				"todo:read books" + lineBreak + 
				"completed:go to work" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test060" + lineBreak,
				"?todo?s/todo/completed/" + lineBreak,
				".-1,.+1p" + lineBreak,
				"/todo/s" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"completed:programming" + lineBreak + 
				"completed:read books" + lineBreak + 
				"completed:go to work" + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command s with no param and there is a command s ahead . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with default address and no param
	 * There is command s ahead
	 */
	@Test
	public void test061() {
		String testFile = "test061";
		String content = "//061s" + lineBreak + 
				".completed:programming.completed:read books.completed:tests." + lineBreak + 
				".todo:surf the Internet.todo:play computer games.todo:write a diary." + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test061" + lineBreak,
				"?todo?s/.todo:/ and /2" + lineBreak,
				".p" + lineBreak,
				"s" + lineBreak,
				".p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				".todo:surf the Internet and play computer games.todo:write a diary." + lineBreak,
				".todo:surf the Internet and play computer games and write a diary." + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command s with default address and no param and there is a command s ahead . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	

	/**
	 * command s with default address and no param
	 * There is command s ahead
	 */
	@Test
	public void test062() {
		String testFile = "test062";
		String content = "//062s" + lineBreak + 
				".completed:programming.completed:read books.completed:tests." + lineBreak + 
				".todo:surf the Internet.todo:play computer games.todo:write a diary." + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test062" + lineBreak,
				"/completed/s/.completed:/ and /2" + lineBreak,
				".p" + lineBreak,
				"s" + lineBreak,
				".p" + lineBreak,
				"s" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				".completed:programming and read books.completed:tests." + lineBreak,
				".completed:programming and read books and tests." + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command s for more times until no match with no param and there is a command s ahead . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with range address composed of /str/ or ?str? address
	 * ???????????????linux???ed???????????????????????????s???????????????????????????????????????????????????????????????ed??????????????????????????????????????????
	 */
	@Test
	public void test063() {
		String testFile = "test063";
		String content = "//063s" + lineBreak + 
				"wing,drawing,justin,listing,tine" + lineBreak + 
				"eating,laugh,bin,inch" + lineBreak + 
				"flying,ink " + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test063" + lineBreak,
				"?stin?,/ink/-1s/ing//2" + lineBreak,
				".p" + lineBreak,
				"?,tine?,/inch/s" + lineBreak,
				".p" + lineBreak,
				"/ing/-1,.s" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"wing,draw,justin,listing,tine" + lineBreak,
				"wing,draw,justin,list,tine" + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command s with no param after command s with /str/,?str? address and param /str1/str2/n . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command s with default address and param /str1/str2/ , no match
	 */
	@Test
	public void test064() {
		String testFile = "test064";
		String content = "//064s" + lineBreak + 
				"flying,ink ,swimming,inner" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test064" + lineBreak,
				"s/ing,ing//" + lineBreak,
				".p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak,
				"flying,ink ,swimming,inner" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command s with default address and param /str1/str2/ but no match . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command p with error address
	 * command q
	 */
	@Test
	public void test065() {
		String testFile = "test065";
		String content = "cn" + lineBreak + "test" + lineBreak + "software" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test065" + lineBreak,
				"$+1p" + lineBreak,
				"/te/p" + lineBreak,
				"?cn?+2,/est/-1p" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak,
				"test" + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command p with some correct and error address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command a,i with some correct and error address
	 * command w,q
	 */
	@Test
	public void test066() {
		String[] inputs = {
				"ed" + lineBreak,
				"3a" + lineBreak,
				"2i" + lineBreak,
				"i" + lineBreak,
				"rgb" + lineBreak,
				"carry up!" + lineBreak,
				"." + lineBreak,
				"-1a" + lineBreak,
				"good job..." + lineBreak,
				"." + lineBreak,
				".=" + lineBreak,
				".-6i" + lineBreak,
				"w test066_2" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak,
				"?" + lineBreak,
				"2" + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command a,i with some correct and error address . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file2 = "test066_2";
		String fileContent2 = "rgb" + lineBreak + "good job..." + lineBreak + "carry up!" + lineBreak;
		
		assertFile(file2, fileContent2, "Test command w after command a and i . The file you save: test066_2's content does not match.");
	}
	
	/**
	 * command c,d with some correct and error address
	 * command W,q
	 */
	@Test
	public void test067() {
		String file2 = "test067_2";
		String content = "test067" + lineBreak;
		createFile(file2, content);
		
		String[] inputs = {
				"ed" + lineBreak,
				"c" + lineBreak,//?
				"d" + lineBreak,//?
				"a" + lineBreak,
				"nan da huang" + lineBreak,
				"muji" + lineBreak,
				"." + lineBreak,
				"1,3c" + lineBreak,//?
				".+1d" + lineBreak,//?
				"W test067_2" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak,
				"?" + lineBreak,
				"?" + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command c,d with some correct and error address . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String fileContent2 = "test067" + lineBreak + "nan da huang" + lineBreak + "muji" + lineBreak;
		
		assertFile(file2, fileContent2, "Test command W after command a,c and d . The file you save: test067_2's content does not match.");
	}
	
	/**
	 * command m with target address before source address
	 */
	@Test
	public void test068() {
		String testFile = "test068";
		String content = "git:before,DJ" + lineBreak + 
				"svn:after,DTT" + lineBreak + 
				"git:in,leet" + lineBreak + 
				"svn:on" + lineBreak + 
				"svn:in,line" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test068" + lineBreak,
				"/in,l/m1" + lineBreak,
				".=" + lineBreak,
				"5m?git:i?" + lineBreak,
				".=" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"2" + lineBreak,
				"3" + lineBreak,
				"git:before,DJ" + lineBreak + "git:in,leet" + lineBreak + "svn:in,line" + lineBreak + 
				"svn:after,DTT" + lineBreak + "svn:on" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command m with target address before source address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}

	/**
	 * command m with target address before range source address
	 */
	@Test
	public void test069() {
		String testFile = "test069";
		String content = "git:a234" + lineBreak + 
				"svn:666" + lineBreak + 
				"git:c123,5241" + lineBreak + 
				"svn:'d+1,$-1" + lineBreak + 
				"svn:e123,521" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test069" + lineBreak,
				"/3,5/,?'d+1,$-1?m1" + lineBreak,
				".=" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"3" + lineBreak,
				"git:a234" + lineBreak + "git:c123,5241" + lineBreak + "svn:'d+1,$-1" + lineBreak + 
				"svn:666" + lineBreak + "svn:e123,521" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command m with target address before range source address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command t with target address between source address
	 */
	@Test
	public void test070() {
		String testFile = "test070";
		String content = "meat:prawn" + lineBreak + 
				"vegetable:carrot" + lineBreak + 
				"food:rice" + lineBreak + 
				"vegetable:cabbage" + lineBreak + 
				"food:noodles" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test070" + lineBreak,
				"1,3t2" + lineBreak,
				".=" + lineBreak,
				"2,-3t2" + lineBreak,
				".=" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"5" + lineBreak,
				"3" + lineBreak,
				
				"meat:prawn" + lineBreak + "vegetable:carrot" + lineBreak + "vegetable:carrot" + lineBreak + 
				"meat:prawn" + lineBreak + "vegetable:carrot" + lineBreak + "food:rice" + lineBreak + 
				"food:rice" + lineBreak + "vegetable:cabbage" + lineBreak + "food:noodles" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command t with target address between source address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command t with range target address before source address
	 */
	@Test
	public void test071() {
		String testFile = "test071";
		String content = "nanjing:The Mausoleum of Dr. Sun Yat-sen" + lineBreak + 
				"beijing:The Imperial Palace" + lineBreak + 
				"shanghai:Disneyland Park,Oriental Pearl TV Tower" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test071" + lineBreak,
				"?jing:The ?,/Park,Oriental/t$-2" + lineBreak,
				".=" + lineBreak,
				",p" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"3" + lineBreak,
				"nanjing:The Mausoleum of Dr. Sun Yat-sen" + lineBreak + "beijing:The Imperial Palace" + lineBreak + 
				"shanghai:Disneyland Park,Oriental Pearl TV Tower" + lineBreak + "beijing:The Imperial Palace" + lineBreak + 
				"shanghai:Disneyland Park,Oriental Pearl TV Tower" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command t with range target address before source address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command j with error address
	 */
	@Test
	public void test072() {
		String testFile = "test072";
		String content = "meat:beef" + lineBreak + 
				"vegetable:cabbage" + lineBreak + 
				"food:noodles" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test072" + lineBreak,
				"j" + lineBreak,
				"$,.-1j" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command j with error address . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * command j with search address composed of /str/ and ?str?
	 */
	@Test
	public void test073() {
		String testFile = "test073";
		String content = "let . be 4 ," + lineBreak + 
				"then 3-1,.-1 is 2,3 ." + lineBreak + 
				"then 2+1,. is 3,4 ." + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test073" + lineBreak,
				"/then/-1,?3,4?+1j" + lineBreak,
				"/1,.-1/-1,?4 ,?+1j" + lineBreak,
				".=" + lineBreak,
				".p" + lineBreak,
				"q" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak,
				"1" + lineBreak,
				"let . be 4 ,then 3-1,.-1 is 2,3 ." + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command j search address composed of /str/ and ?str? . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * error using of address combining with + and -
	 */
	@Test
	public void test074() {
		String testFile = "test074";
		String content = "meat:beef" + lineBreak + 
				"vegetable:cabbage" + lineBreak + 
				"food:noodles" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test074" + lineBreak,
				"/cab/-?t:b?p" + lineBreak,
				"$-$a" + lineBreak,
				";+2w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak,
				"?" + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Error using of address combining with + and - (such as $-/str/) . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * error input of address
	 */
	@Test
	public void test075() {
		String testFile = "test075";
		String content = "meat:beef" + lineBreak + 
				"vegetable:cabbage" + lineBreak + 
				"food:noodles" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test075" + lineBreak,
				"/wwzz?p" + lineBreak,
				".$a" + lineBreak,
				"m,n-1c" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak,
				"?" + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Error input of address (such as /str?,containing character and so on) . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	/**
	 * error using of command
	 */
	@Test
	public void test076() {
		String testFile = "test076";
		String content = "meat:beef" + lineBreak + 
				"vegetable:cabbage" + lineBreak + 
				"food:rice" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test076" + lineBreak,
				"2d" + lineBreak,
				";Q" + lineBreak,
				"$f" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"?" + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Error using of command (such as adding an address to the command without address and so on) . Your output does not match!", arrayToString(outputs), outputStream.toString());
	}
	
	//????????????
	/**
	 * command i,=,p,m,w
	 */
	@Test
	public void test077() {
		String testFile = "test077";
		String content = "edu.nju.software" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test077" + lineBreak,
				"i" + lineBreak,
				"com.test.ware" + lineBreak,
				"hello.edu.note" + lineBreak,
				"." + lineBreak,
				"2=" + lineBreak,
				"/edu/p" + lineBreak,
				".m1" + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"2" + lineBreak,
				"edu.nju.software" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		assertEquals("Test command i,=,p,m . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test077";
		String fileContent = "com.test.ware" + lineBreak + 
				"edu.nju.software" + lineBreak + 
				"hello.edu.note" + lineBreak;
		
		assertFile(file, fileContent, "Test command i,=,p,m,w .The file you save: test077's content does not match.");
	}
	
	/**
	 * command a,p,t,=,s,w
	 */
	@Test
	public void test078() {
		String testFile = "test078";
		String content = "software+" + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test078" + lineBreak,
				"a" + lineBreak,
				"hardware+ pipeline" + lineBreak,
				"love soft drinks." + lineBreak,
				"." + lineBreak,
				"$-2,/ware/p" + lineBreak,
				"3t?ware+?-1" + lineBreak,
				".=" + lineBreak,
				"2s/soft/cold/" + lineBreak,
				"w" + lineBreak,
				"Q" + lineBreak
		};
		
		String[] outputs = {
				"software+" + lineBreak,
				"2" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command a,p,t,=,s . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test078";
		String fileContent = "software+" + lineBreak + 
				"love cold drinks." + lineBreak + 
				"hardware+ pipeline" + lineBreak + 
				"love soft drinks." + lineBreak;
		
		assertFile(file, fileContent, "Test command a,p,t,=,s,w .The file you save: test078's content does not match.");
	}
	
	/**
	 * command z,t,p,j,f,w
	 */
	@Test
	public void test079() {
		String testFile = "test079";
		String content = "wear:" + lineBreak + 
				"Smartwatch." + lineBreak + 
				"Bluetooth headset." + lineBreak + 
				"bracelet." + lineBreak;
		createFile(testFile, content);
		
		String[] inputs = {
				"ed test079" + lineBreak,
				"?wear?+1z1" + lineBreak,
				"1,2t$" + lineBreak,
				"1,$-2j" + lineBreak,
				".+1p" + lineBreak,
				";j" + lineBreak,
				"f" + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak
		};
		
		String[] outputs = {
				"Smartwatch." + lineBreak + "Bluetooth headset." + lineBreak,
				"wear:" + lineBreak,
				"test079" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command z,t,p,j,f,w . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test079";
		String fileContent = "wear:Smartwatch.Bluetooth headset.bracelet." + lineBreak + 
				"wear:Smartwatch." + lineBreak;
		
		assertFile(file, fileContent, "Test command z,t,p,j,f,w .The file you save: test079's content does not match.");
	}

	/**
	 * command a,d,c,p,f,w,q
	 */
	@Test
	public void test80() {
		String[] inputs = {
				"ed" + lineBreak,
				"a" + lineBreak,
				"Congratuations!" + lineBreak,
				"situations!" + lineBreak,
				"." + lineBreak,
				"?tions!?,/tuations=/d" + lineBreak,
				"?tuati?,/s!/c" + lineBreak,
				"sure?" + lineBreak,
				"/" + lineBreak,
				"." + lineBreak,
				"/?/p" + lineBreak,
				"?/?p" + lineBreak,
				"f" + lineBreak,
				"f test80" + lineBreak,
				"f test80_2" + lineBreak,
				"w" + lineBreak,
				"q" + lineBreak,
		};
		
		String[] outputs = {
				"?" + lineBreak,
				"sure?" + lineBreak,
				"/" + lineBreak,
				"?" + lineBreak
		};
		
		inputStream = new ByteArrayInputStream(arrayToString(inputs).getBytes());
		System.setIn(inputStream);
		
		EDLineEditor.main(null);
		
		assertEquals("Test command a,d,c,p,f,w,q . Your output does not match!", arrayToString(outputs), outputStream.toString());
		
		String file = "test80_2";
		String fileContent = "sure?" + lineBreak + 
				"/" + lineBreak + 
				"situations!" + lineBreak;
		
		assertFile(file, fileContent, "Test command a,d,c,p,f,w,q . The file you save: test80_2's content does not match.");
	}
	
	private String arrayToString(String[] array) {
		StringBuffer buffer = new StringBuffer();
		for(String str:array) {
 			buffer.append(str);
		}
		return buffer.toString();
	}
	
	private void assertFile(String file, String expect, String failMessage){
		StringBuffer buffer = new StringBuffer();
		if(new File(file).exists()) {
			try {
				BufferedReader br = new BufferedReader(new FileReader(file));
				String line = null;
				while((line=br.readLine())!=null) {
					buffer.append(line+lineBreak);
				}
				br.close();
			} catch (FileNotFoundException e1) {
				e1.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		assertEquals(failMessage, expect, buffer.toString());
	}
	
	private void createFile(String file, String content) {
		try {
			BufferedWriter bw = new BufferedWriter(new FileWriter(file));
			bw.write(content);
			bw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
}
