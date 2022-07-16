//
//  StockGraph.swift
//  iza-project (iOS)
//
//  Created by Zdeněk Lapeš on 5/27/22.
//

import Foundation
import SwiftUI
import SwiftYFinance
import SwiftUICharts

struct StockGraphView: View {
    @State var symbol: String
    @State var interval: ChartTimeInterval = .oneday
    @State var data: LineChartData?
    @State var chartData: [StockChartData]?
    @State var high52w: Float?
    @State var low52w: Float?
    let MAX : Float = 100000000.0
    let format :String = "%.2f"
    
    //
    var body: some View {
        if chartData != nil, data != nil {
            Section {
                VStack {
                    LineChart(chartData: data!)
                        .pointMarkers(chartData: data!)
                        .touchOverlay(chartData: data!, specifier: self.format)
                        .xAxisGrid(chartData: data!)
                        .yAxisGrid(chartData: data!)
                        .xAxisLabels(chartData: data!)
                        .yAxisLabels(chartData: data!)
                        .headerBox(chartData: data!)
                        .infoBox(chartData: data!)
                        .id(data!.id)
                        .frame(minWidth: 150, maxWidth: 900, minHeight: 150, idealHeight: 250, maxHeight: 400, alignment: .center)
                }.padding(.horizontal)
            }.padding(.bottom, 10)
        } else if chartData == nil {
            Text("No Chart Data...").onAppear() { fetchChart(); fetchData() }
        } else if data == nil {
            Text("No data...").onAppear() { self.data = weekOfData() }
        }
    }
}

// source: https://stackoverflow.com/a/58065902/14471542
extension Date {
    func get(_ components: Calendar.Component..., calendar: Calendar = Calendar.current) -> DateComponents {
        return calendar.dateComponents(Set(components), from: self)
    }
    
    func get(_ component: Calendar.Component, calendar: Calendar = Calendar.current) -> Int {
        return calendar.component(component, from: self)
    }
}

extension StockGraphView {
    func weekOfData() -> LineChartData? {
        guard let _chartData = chartData else {
            return nil
        }
        let dataPoints = prepareDataPoints(chartData: _chartData)
        //
        let data = LineDataSet(dataPoints: dataPoints,
                               pointStyle: PointStyle(pointSize: 0, borderColour: .blue, fillColour: .blue, lineWidth: 0, pointType: .filled, pointShape: .circle),
                               style: LineStyle(lineColour: ColourStyle(colour: .red), lineType: .curvedLine))
        //
        let metadata = ChartMetadata(title: "52 weeks", subtitle: "")
        //
        let gridStyle = GridStyle(numberOfLines: 10,
                                  lineColour: Color(.lightGray).opacity(0.5),
                                  lineWidth: 1,
                                  dash: [8],
                                  dashPhase: 0)
        //
        let chartStyle = LineChartStyle(infoBoxPlacement: .infoBox(isStatic: false),
                                        infoBoxBorderColour: Color.primary,
                                        infoBoxBorderStyle: StrokeStyle(lineWidth: 1),
                                        
                                        markerType: .vertical(attachment: .line(dot: .style(DotStyle()))),
                                        
                                        xAxisGridStyle: gridStyle,
                                        xAxisLabelPosition: .bottom,
                                        xAxisLabelColour: Color.primary,
                                        xAxisLabelsFrom: .dataPoint(rotation: .degrees(0)),
                                        
                                        
                                        yAxisGridStyle: gridStyle,
                                        yAxisLabelPosition: .leading,
                                        yAxisLabelColour: Color.primary,
                                        yAxisNumberOfLabels: 7,
                                        
                                        globalAnimation: .easeOut(duration: 1))
        //
        return LineChartData(dataSets: data,
                             metadata: metadata,
                             chartStyle: chartStyle)
        
    }
    
    //
    func fetchChart() {
        let date = Date(timeIntervalSinceNow: -1 * 60 * 60 * 24 * 370) // -1 * secPerMin * minPerHour * hoursPerDay * (daysPerYear + 5)
        SwiftYFinance.chartDataBy(identifier: self.symbol, start: date, interval: self.interval) { data, error in
            if let error = error { print("FINANCE", error); return }
            self.chartData = data!
        }
    }
    
    //
    func fetchData() {
        SwiftYFinance.summaryDataBy(identifier: self.symbol) { data, error in
            if let error = error { print("FINANCE", error); return }
            self.high52w = data?.summaryDetail?.fiftyTwoWeekHigh?.round(to: 2)
            self.low52w = data?.summaryDetail?.fiftyTwoWeekLow?.round(to: 2)
        }
    }
    
    //
    func prepareDataPoints(chartData: [StockChartData]) -> [LineChartDataPoint] {
        //
        func shouldBeXAxesLabel(i: Int, step: Int) -> Bool {
            return (
                i == step * 0 || i == step * 1 || i == step * 2 || i == step * 3 || i == step * 4 ||
                i == step * 5 || i == step * 6 || i == step * 7 || i == step * 8 || i == step * 9 ||
                i == step * 10 || i == step * 11
            )
        }
        
        //
        var dataPoints: [LineChartDataPoint] = []
        for i in (0..<chartData.count) {
            dataPoints.append(LineChartDataPoint(value: Double(chartData[i].close ?? 0.0)))
        }
        
        //
        for i in (0..<chartData.count) {
            if (shouldBeXAxesLabel(i: i, step: dataPoints.count / 12)) {
                dataPoints[i].xAxisLabel = "\(chartData[i].date?.get(.month) ?? 0)"
            } else {
                dataPoints[i].xAxisLabel = ""
            }
        }
        
        //
        dataPoints[dataPoints.count - 1].xAxisLabel = "Now"
        return dataPoints
    }
}
