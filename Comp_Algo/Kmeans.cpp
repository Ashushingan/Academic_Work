#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <algorithm>

using namespace std;

struct Point {
    double x = 0.0;
    double y = 0.0;
    int cluster = -1;
};

double calculateDistance(const Point& p1, const Point& p2);
void assignToClusters(vector<Point>& points, const vector<Point>& centroids);
bool updateCentroids(const vector<Point>& points, vector<Point>& centroids);
void kMeans(vector<Point>& points, int k, int max_iterations);

int main() {
    int k = 30;
    int max_iterations = 10000;
    int num_points = 12000;

    // --- Data Generation ---
    // Generate a large number of random points for clustering.
    vector<Point> points;
    points.reserve(num_points); // Pre-allocate memory for efficiency

    random_device rd;
    mt19937 gen(rd());
    // Create three distinct groups of points for more realistic clustering
    uniform_real_distribution<> distrib_group1(0.0, 20.0);
    uniform_real_distribution<> distrib_group2(30.0, 50.0);
    uniform_real_distribution<> distrib_group3(60.0, 80.0);

    for (int i = 0; i < num_points; ++i) {
        if (i < num_points / 3) {
            points.push_back({distrib_group1(gen), distrib_group1(gen)});
        } else if (i < (num_points * 2) / 3) {
            points.push_back({distrib_group2(gen), distrib_group2(gen)});
        } else {
            points.push_back({distrib_group3(gen), distrib_group3(gen)});
        }
    }

    cout << "Generated " << num_points << " points." << endl;
    cout << "Running K-Means with k = " << k << "..." << endl;

    // Run the K-Means algorithm
    kMeans(points, k, max_iterations);

    cout << "\n--- Clustering Complete ---" << endl;
    
    // Optional: Print final centroids to verify they are in different regions
    // Note: The actual cluster contents are not printed to keep the output clean.
    // The main goal here is to generate a performance profile.
    
    return 0;
}

double calculateDistance(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void assignToClusters(vector<Point>& points, const vector<Point>& centroids) {
    for (auto& point : points) {
        double min_dist = numeric_limits<double>::max();
        int closest_centroid_index = -1;

        for (int i = 0; i < centroids.size(); ++i) {
            double dist = calculateDistance(point, centroids[i]);
            if (dist < min_dist) {
                min_dist = dist;
                closest_centroid_index = i;
            }
        }
        point.cluster = closest_centroid_index;
    }
}

bool updateCentroids(const vector<Point>& points, vector<Point>& centroids) {
    vector<Point> new_centroids(centroids.size(), {0.0, 0.0, -1});
    vector<int> cluster_counts(centroids.size(), 0);

    for (const auto& point : points) {
        if (point.cluster != -1) {
            new_centroids[point.cluster].x += point.x;
            new_centroids[point.cluster].y += point.y;
            cluster_counts[point.cluster]++;
        }
    }

    for (int i = 0; i < new_centroids.size(); ++i) {
        if (cluster_counts[i] > 0) {
            new_centroids[i].x /= cluster_counts[i];
            new_centroids[i].y /= cluster_counts[i];
        } else {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, points.size() - 1);
            new_centroids[i] = points[dis(gen)];
        }
    }

    bool changed = false;
    for (int i = 0; i < centroids.size(); ++i) {
        if (centroids[i].x != new_centroids[i].x || centroids[i].y != new_centroids[i].y) {
            changed = true;
            break;
        }
    }

    centroids = new_centroids;
    return changed;
}

void kMeans(vector<Point>& points, int k, int max_iterations) {
    if (points.size() < k) {
        cerr << "Error: Number of points is less than k." << endl;
        return;
    }

    vector<Point> centroids;
    random_device rd;
    mt19937 gen(rd());
    vector<int> indices(points.size());
    for(int i = 0; i < indices.size(); ++i) indices[i] = i;
    shuffle(indices.begin(), indices.end(), gen);

    for (int i = 0; i < k; ++i) {
        centroids.push_back(points[indices[i]]);
    }

    for (int i = 0; i < max_iterations; ++i) {
        assignToClusters(points, centroids);
        bool changed = updateCentroids(points, centroids);

        if (!changed) {
            cout << "Convergence reached after " << i + 1 << " iterations." << endl;
            break; 
        }
    }
}
