package code_graph_generator;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class FileSystem {

    private String fileName;
    private ArrayList<String> fileRows;
    private int numOfMatrices;

    public FileSystem(String file) {
        fileName = file;
        fileRows = new ArrayList<String>();
        this.numOfMatrices = 0;
        readFile(fileName);
    }

    public void readFile(String fileName) {

        String line = null;
        int counter = 0;
        try {
            // FileReader reads text files in the default encoding.
            FileReader fileReader = new FileReader(fileName);

            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader = new BufferedReader(fileReader);

            while ((line = bufferedReader.readLine()) != null) {
                fileRows.add(line);
                if (line.contentEquals("")) counter++;
            }

            // Always close files.
            bufferedReader.close();
            this.numOfMatrices = counter + 1;
        } catch (FileNotFoundException ex) {
            System.out.println("Unable to open file '" + fileName + "'");
        } catch (IOException ex) {
            System.out.println("Error reading file '" + fileName + "'");
        }

    }

    public void writeFile(String fileName, String temp) {

        try {
            // Assume default encoding.
            FileWriter fileWriter = new FileWriter(fileName);

            // Always wrap FileWriter in BufferedWriter.
            BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);

            bufferedWriter.write(temp);

            // Always close files.
            bufferedWriter.close();
        } catch (IOException ex) {
            System.out.println("Error writing to file '" + fileName + "'");
        }
    }

    public ArrayList<String> getFileRows() {
        return fileRows;
    }

    public int[][] getAdjMatrix() {
        int[][] adjMatrix = findMatrix(fileRows, 0);
        return adjMatrix;
    }

    public int[][] getBandwidthMatrix() {
        int[][] linkMatrix = findMatrix(fileRows, 1);
        return linkMatrix;
    }

    public int[][] getDelayMatrix() {
        int[][] delayMatrix = findMatrix(fileRows, 2);
        return delayMatrix;
    }

    public int[][] getReliabilityMatrix() {
        int[][] reliabilityMatrix = findMatrix(fileRows, 3);
        return reliabilityMatrix;
    }

    public int[][] getSpectrumStartIndex() {
        int[][] spectrumStartIndex = findMatrix(fileRows, 4);
        return spectrumStartIndex;
    }

    public int[][] findMatrix(ArrayList<String> fileRows, int type) {

        int[][] temp;
        String row[];
        int start;

        temp = new int[fileRows.size() / numOfMatrices][fileRows.size() / numOfMatrices];
        row = new String[fileRows.size() / numOfMatrices];
        start = type * fileRows.size() / numOfMatrices;

        if (type != 0) start = start + 1;

        for (int i = start; i < start + fileRows.size() / numOfMatrices; i++) {
            if (fileRows.get(i).length() != 0) {

                row = fileRows.get(i).split("\t");

                for (int j = 0; j < row.length; j++) {
                    temp[i - start][j] = Integer.valueOf(row[j]);

                }

            }
        }

        return temp;
    }

}