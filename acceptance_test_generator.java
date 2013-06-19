import java.util.Random;
import java.util.Vector;

public class test {
	// A graph representing the partial ordering
	public static int[][] pfd_graph = new int[101][101];
	public static Vector<Integer> total_vertices = new Vector<Integer>();
	public static Vector<Integer> previous_vertices = new Vector<Integer>();

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		int size = 1; // Number of vertices in the graph
		int current = 1; // Number of vertices in the current layer
		int param = 1; // Number of prerequisites for the current vertex

		/* initialize random seed: */
		Random r1 = new Random();

		for (int n = 0; n < 1000; n++) {
			/* Generate a random acyclic graph */
			// Clear previous settings
			pfd_graph = new int[101][101];
			clear_graph();
			total_vertices.clear();
			previous_vertices.clear();

			// Generate size of graph
			size = r1.nextInt(10) + 1;

			// Generate a random arrangement of elements
			random_tv(size);

			while (total_vertices.size() != 0) {
				current = r1.nextInt(total_vertices.size()) + 1;

				if (previous_vertices.size() != 0) {
					for (int i = 0; i < current; i++) {
						random_pv();

						// Generate the number of parameters for the vector
						param = r1.nextInt(previous_vertices.size()) + 1;

						// Select the vector
						int x = total_vertices.lastElement();
						total_vertices.removeElementAt(total_vertices.size() - 1);

						pfd_graph[x][0] = param;
						for (int j = 1; j <= param; j++) {
							pfd_graph[x][j] = previous_vertices.elementAt(j - 1);
						}
					}
				} else {
					for (int i = 0; i < current; i++) {
						previous_vertices.add(total_vertices.lastElement());
						total_vertices.removeElementAt(total_vertices.size() - 1);
					}
				}
			}

			// Print the array
			System.out.println(size + " " + (size - previous_vertices.size()));
			for (int i = 1; i <= size; i++) {
				if (pfd_graph[i][0] != -1) {
					System.out.print(i + " " + pfd_graph[i][0]);
					for (int j = 1; j <= pfd_graph[i][0]; j++) {
						System.out.print(" " + pfd_graph[i][j]);
					}
					System.out.println();
				}
			}
			System.out.println();
		}

	}

	private static void clear_graph() {
		// Initialize pfd_graph to the initial_value
		for (int i = 0; i < 101; i++) {
			for (int j = 0; j < 101; j++) {
				pfd_graph[i][j] = -1;
			}
		}
	}

	public static void random_tv(int size) {
		int temp = 0;
		int random = 0;

		/* initialize random seed: */
		Random r1 = new Random();

		// Add elements to vector
		for (int i = 1; i <= size; i++) {
			total_vertices.add(i);
		}

		// Randomize Vector
		for (int j = 0; j < size; j++) {
			random = r1.nextInt(size);
			temp = total_vertices.elementAt(j);
			total_vertices.setElementAt(total_vertices.elementAt(random), j);
			total_vertices.setElementAt(temp, random);
		}
	}

	public static void random_pv() {
		int temp = 0;
		int random = 0;

		/* initialize random seed: */
		Random r1 = new Random();

		// Randomize Vector
		for (int i = 0; i < previous_vertices.size(); i++) {
			random = r1.nextInt(previous_vertices.size());
			temp = previous_vertices.elementAt(i);
			previous_vertices.setElementAt(previous_vertices.elementAt(random), i);
			previous_vertices.setElementAt(temp, random);
		}
	}

}
