#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

class MeetingPointFinder {
public:
    Point findMedianMeetingPoint(const std::vector<Point>& clients) {
        std::vector<int> xCoordinates, yCoordinates;
        for (std::vector<Point>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
            xCoordinates.push_back(it->x);
            yCoordinates.push_back(it->y);
        }
        std::sort(xCoordinates.begin(), xCoordinates.end());
        std::sort(yCoordinates.begin(), yCoordinates.end());

        int medianX = xCoordinates[xCoordinates.size() / 2];
        int medianY = yCoordinates[yCoordinates.size() / 2];

        return Point(medianX, medianY);
    }

    Point findCentroidMeetingPoint(const std::vector<Point>& clients) {
        int totalX = 0, totalY = 0;
        for (std::vector<Point>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
            totalX += it->x;
            totalY += it->y;
        }
        int centroidX = totalX / clients.size();
        int centroidY = totalY / clients.size();

        return Point(centroidX, centroidY);
    }

    int calculateTotalDistance(const std::vector<Point>& clients, const Point& meetingPoint) {
        int totalDistance = 0;
        for (std::vector<Point>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
            totalDistance += abs(it->x - meetingPoint.x) + abs(it->y - meetingPoint.y);
        }
        return totalDistance;
    }
};

int main() {
    std::vector<Point> clients;
    clients.push_back(Point(1, 3));
    clients.push_back(Point(2, 5));
    clients.push_back(Point(5, 6));
    clients.push_back(Point(7, 2));

    MeetingPointFinder meetingPointFinder;

    Point medianMeetingPoint = meetingPointFinder.findMedianMeetingPoint(clients);
    int medianTotalDistance = meetingPointFinder.calculateTotalDistance(clients, medianMeetingPoint);
    std::cout << "Median Meeting Point: (" << medianMeetingPoint.x << ", " << medianMeetingPoint.y << ")" << std::endl;
    std::cout << "Total Distance to Median Meeting Point: " << medianTotalDistance << std::endl;

    Point centroidMeetingPoint = meetingPointFinder.findCentroidMeetingPoint(clients);
    int centroidTotalDistance = meetingPointFinder.calculateTotalDistance(clients, centroidMeetingPoint);
    std::cout << "Centroid Meeting Point: (" << centroidMeetingPoint.x << ", " << centroidMeetingPoint.y << ")" << std::endl;
    std::cout << "Total Distance to Centroid Meeting Point: " << centroidTotalDistance << std::endl;

    return 0;
}
