import plotly.graph_objects as go

# Create a blank figure
fig = go.Figure()

# Define class positions
stock_pos = [1, 0]
investment_pos = [4, 0]
portfolio_pos = [7, 0]

# Class box dimensions
box_width = 2.2
box_height = 3.0

# Create class boxes
classes = [
    {"name": "Stock", "pos": stock_pos, "color": "#1FB8CD"},
    {"name": "Investment", "pos": investment_pos, "color": "#FFC185"},
    {"name": "Portfolio", "pos": portfolio_pos, "color": "#ECEBD5"}
]

# Add class boxes
for cls in classes:
    x0 = cls["pos"][0] - box_width/2
    x1 = cls["pos"][0] + box_width/2
    y0 = cls["pos"][1] - box_height/2
    y1 = cls["pos"][1] + box_height/2
    
    # Main class box
    fig.add_shape(
        type="rect",
        x0=x0, y0=y0, x1=x1, y1=y1,
        line=dict(color="black", width=1.5),
        fillcolor=cls["color"]
    )
    
    # Divider lines (to separate class name, attributes, methods)
    y_div1 = y1 - 0.5  # Divider after class name
    y_div2 = y0 + 1.5  # Divider between attributes and methods
    
    fig.add_shape(
        type="line",
        x0=x0, y0=y_div1, x1=x1, y1=y_div1,
        line=dict(color="black", width=1.5)
    )
    
    fig.add_shape(
        type="line",
        x0=x0, y0=y_div2, x1=x1, y1=y_div2,
        line=dict(color="black", width=1.5)
    )

# Add class names
for cls in classes:
    fig.add_annotation(
        x=cls["pos"][0], y=cls["pos"][1] + box_height/2 - 0.25,
        text=f"<b>{cls['name']}</b>",
        showarrow=False,
        font=dict(size=16)
    )

# Add attributes and methods (shortened to fit 15 char limit)
# Stock class
fig.add_annotation(
    x=stock_pos[0], y=stock_pos[1] + 0.75,
    text="- symbol: str<br>- companyName<br>- currentPrice<br>- previousPrice",
    showarrow=False,
    font=dict(size=12)
)
fig.add_annotation(
    x=stock_pos[0], y=stock_pos[1] - 0.75,
    text="+ constructors<br>+ getters<br>+ setters<br>+ getPriceChg()<br>+ getPercentChg()",
    showarrow=False,
    font=dict(size=12)
)

# Investment class
fig.add_annotation(
    x=investment_pos[0], y=investment_pos[1] + 0.75,
    text="- stock: Stock*<br>- sharesOwned<br>- purchasePrice<br>- totalInvested",
    showarrow=False,
    font=dict(size=12)
)
fig.add_annotation(
    x=investment_pos[0], y=investment_pos[1] - 0.75,
    text="+ constructors<br>+ getters<br>+ setters<br>+ getCurrentVal()<br>+ getGainLoss()",
    showarrow=False,
    font=dict(size=12)
)

# Portfolio class
fig.add_annotation(
    x=portfolio_pos[0], y=portfolio_pos[1] + 0.75,
    text="- investments<br>- portfolioName<br>- totalInitInv",
    showarrow=False,
    font=dict(size=12)
)
fig.add_annotation(
    x=portfolio_pos[0], y=portfolio_pos[1] - 0.75,
    text="+ constructors<br>+ addInvestment<br>+ removeInvest<br>+ getCurrentVal<br>+ sortInvest<br>+ fileIO",
    showarrow=False,
    font=dict(size=12)
)

# Draw relationship lines
# Portfolio "composes" Investment (composition - filled diamond)
fig.add_shape(
    type="line",
    x0=portfolio_pos[0] - box_width/2,
    y0=portfolio_pos[1],
    x1=investment_pos[0] + box_width/2 + 0.3,
    y1=investment_pos[1],
    line=dict(color="black", width=1.5)
)

# Add filled diamond for composition using path
diamond_size = 0.15
x_mid = investment_pos[0] + box_width/2 + 0.15
y_mid = investment_pos[1]

# Create filled diamond for composition using SVG path
diamond_path = f"M {x_mid-diamond_size} {y_mid} L {x_mid} {y_mid+diamond_size} L {x_mid+diamond_size} {y_mid} L {x_mid} {y_mid-diamond_size} Z"
fig.add_shape(
    type="path",
    path=diamond_path,
    line=dict(color="black"),
    fillcolor="black"
)

# Investment "aggregates" Stock (aggregation - empty diamond)
fig.add_shape(
    type="line",
    x0=investment_pos[0] - box_width/2,
    y0=investment_pos[1],
    x1=stock_pos[0] + box_width/2 + 0.3,
    y1=stock_pos[1],
    line=dict(color="black", width=1.5)
)

# Add empty diamond for aggregation
x_mid = stock_pos[0] + box_width/2 + 0.15
y_mid = stock_pos[1]

# Create empty diamond for aggregation using SVG path
diamond_path = f"M {x_mid-diamond_size} {y_mid} L {x_mid} {y_mid+diamond_size} L {x_mid+diamond_size} {y_mid} L {x_mid} {y_mid-diamond_size} Z"
fig.add_shape(
    type="path",
    path=diamond_path,
    line=dict(color="black"),
    fillcolor="white"
)

# Add relationship descriptions
fig.add_annotation(
    x=(portfolio_pos[0] + investment_pos[0])/2,
    y=portfolio_pos[1] + 0.3,
    text="composition",
    showarrow=False,
    font=dict(size=10)
)

fig.add_annotation(
    x=(investment_pos[0] + stock_pos[0])/2,
    y=investment_pos[1] + 0.3,
    text="aggregation",
    showarrow=False,
    font=dict(size=10)
)

# Update layout
fig.update_layout(
    title="UML Class Diagram",
    showlegend=False,
    plot_bgcolor="white"
)

# Set axes ranges and disable axes
fig.update_xaxes(
    range=[-0.5, 8.5],
    showticklabels=False,
    showgrid=False,
    zeroline=False,
    visible=False
)

fig.update_yaxes(
    range=[-2, 2],
    showticklabels=False,
    showgrid=False,
    zeroline=False,
    visible=False,
    scaleanchor="x",
    scaleratio=1
)

# Save the figure
fig.write_image("uml_class_diagram.png")

fig.show()