#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <string>

	std::multimap<std::string, std::string> routesT = {
	{"DSM", "ORD"},
	{"ORD", "BGI"},
	{"BGI", "LGA"},
	{"SIN", "CDG"},
	{"CDG", "SIN"},
	{"CDG", "BUD"},
	{"DEL", "DOH"},
	{"DEL", "CDG"},
	{"TLV", "DEL"},
	{"EWR", "HND"},
	{"HND", "ICN"},
	{"HND", "JFK"},
	{"ICN", "JFK"},
	{"JFK", "LGA"},
	{"EYW", "LHR"},
	{"LHR", "SFO"},
	{"SFO", "SAN"},
	{"SFO", "DSM"},
	{"SAN", "EYW"}
};
	std::multimap<std::string, std::string> switchedRoutesT = {
    {"ORD", "DSM"},
    {"BGI", "ORD"},
    {"LGA", "BGI"},
    {"CDG", "SIN"},
    {"SIN", "CDG"},
    {"BUD", "CDG"},
    {"DOH", "DEL"},
    {"CDG", "DEL"},
    {"DEL", "TLV"},
    {"HND", "EWR"},
    {"ICN", "HND"},
    {"JFK", "HND"},
    {"JFK", "ICN"},
    {"LGA", "JFK"},
    {"LHR", "EYW"},
    {"SFO", "LHR"},
    {"SAN", "SFO"},
    {"DSM", "SFO"},
    {"EYW", "SAN"}
};


void print_routes(std::vector<std::string> route)
{
	for (auto it = route.begin(); it != route.end(); it++)
	{
		std::cout << *it;
		if (it + 1 != route.end())
			std::cout << " -> ";
	}
	std::cout << std::endl;
}


std::vector<std::string> solve(std::string start, std::string target, std::vector<std::string> forward_route = {}, std::vector<std::string> backward_route = {}, int current_depth = 0, std::multimap<std::string, std::string> switchedRoutes = switchedRoutesT, std::multimap<std::string, std::string> routes = routesT)
{


	std::vector<std::string> result;
	std::multimap<std::string, std::string> croutes;
	
	
	std::cout << "Start: " << start << " , Target: " << target << ", current depth: " << current_depth << std::endl;

	if (current_depth >= routes.size())
	{
		std::vector<std::string> noresult = {};
		return (noresult);
	}

	if (current_depth % 2)
		croutes = switchedRoutes;
	else
		croutes = routes;


	auto range = croutes.equal_range(start);
	for (auto it = range.first; it != range.second; it++)
	{
		//if a path is found
		if (it->second == target)
		{
			std::cout << "Routes found " << std::endl;
			if (current_depth % 2)
			{
				backward_route.push_back(it->first);
				backward_route.push_back(it->second);
			}
			else
			{
				forward_route.push_back(it->first);
				forward_route.push_back(it->second);
			}
			
			result.reserve(forward_route.size() + backward_route.size());
			result.insert(result.end(), forward_route.begin(), forward_route.end());
			result.insert(result.end(), backward_route.rbegin(), backward_route.rend());
			//print_routes(result);
			print_routes(forward_route);
			print_routes(backward_route);

			return (result);
		}
		else
		{

			auto s = it->second;	
			if (current_depth % 2)
			{
				backward_route.push_back(start);
				auto next_it = std::next(it);
				switchedRoutes.erase(it);
				it = next_it;
			}
			else
			{
				forward_route.push_back(start);
				auto next_it = std::next(it);
				routes.erase(it);
				it = next_it;
			}
			result = solve(target, s, forward_route, backward_route, current_depth + 1);
		}

	}
	return (result);
}


int main()
{
	std::vector<std::string> result = solve("HND", "LGA");
	if (result.empty() == true)
	{
		std::cout << "No routes found" << std::endl;
	}
	else
	{
		print_routes(result);
	}
	return 0;

}
