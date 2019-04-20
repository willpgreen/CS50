import os
import sqlalchemy

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached

class SQL(object):
    def __init__(self, url):
        try:
            self.engine = sqlalchemy.create_engine(url)
        except Exception as e:
            raise RuntimeError(e)
    def execute(self, text, *multiparams, **params):
        try:
            statement = sqlalchemy.text(text).bindparams(*multiparams, **params)
            result = self.engine.execute(str(statement.compile(compile_kwargs={"literal_binds": True})))
            # SELECT
            if result.returns_rows:
                rows = result.fetchall()
                return [dict(row) for row in rows]
            # INSERT
            elif result.lastrowid is not None:
                return result.lastrowid
            # DELETE, UPDATE
            else:
                return result.rowcount
        except sqlalchemy.exc.IntegrityError:
            return None
        except Exception as e:
            raise RuntimeError(e)

@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # check users cash
    cash = float(db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])[0]["cash"])

    # pull stocks for user
    stocks = db.execute("SELECT symbol, SUM(shares) as shares_total \
            FROM transactions WHERE user = :user \
            GROUP BY symbol", user=session["user_id"])

  # create variable to store total value of users portolio
    value = cash

    # update info for each stock
    for stock in stocks:
        stock.update({"name": lookup(stock["symbol"])["name"]})
        stock.update({"price": lookup(stock["symbol"])["price"]})
        stock.update({"total": stock["price"]*stock["shares_total"]})
        value += stock["total"]

    # remove stocks user no longer owns
    stocks = [stock for stock in stocks if int(stock["shares_total"]) > 0]

    return render_template("index.html", value=value, stocks=stocks, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")
    else:
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol")

        # Ensure shares were submitted
        if not request.form.get("shares"):
            return apology("missing shares")

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("must be a number")

        if int(request.form.get("shares")) < 0:
            return apology("shares must be positive number")

        # lookup stock info
        quote = lookup(request.form.get("symbol"))

        # Check symbol is valid
        if not quote:
            return apology("invalid symbol")

        # Store stock information
        name = quote["name"]
        price = quote["price"]
        symbol = quote["symbol"]

        # store user input
        shares = request.form.get("shares")
        cost = int(shares) * float(price)

        # check users cash
        cash = float(db.execute("SELECT cash FROM users WHERE id = :id",
                                id=session["user_id"])[0]["cash"])

        # make sure user can afford stock
        if cost > cash:
            return apology("can't afford")

        # update transactions data base
        db.execute("INSERT INTO transactions (user, shares, symbol, price, transacted) \
                VALUES(:user, :shares, :symbol, :price, :transacted)",
                   user=session["user_id"],
                   shares=shares,
                   symbol=symbol,
                   price=int(price * 100),
                   transacted=datetime.now())

        # update users cash
        db.execute("UPDATE users SET cash = cash - :cost WHERE id = :id",
                   id=session["user_id"], cost=cost)

        # Redirect user to home page
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # pull users transactions
    stocks = db.execute("Select symbol, shares, price, transacted FROM transactions \
             WHERE user = :user GROUP BY transacted", user=session["user_id"])

    # price needs to be converted back to dollars
    for stock in stocks:
        stock.update({"price": stock["price"]/100})

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "GET":
        return render_template("quote.html")

    else:
        # check for input
        if not request.form.get("symbol"):
            return apology("missing symbol")

        # lookup and store stock info
        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("invalid symbol")

        name = quote["name"]
        price = quote["price"]
        symbol = quote["symbol"]

        return render_template("price.html", name=name, symbol=symbol, price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    def number_check(s):
        '''Check if string contains number'''
        return any(c.isdigit() for c in s)

    def lower_check(s):
        '''Check string contains lowercase'''
        return any(c.islower() for c in s)

    def upper_check(s):
        '''Check string contains lowercase'''
        return any(c.isupper() for c in s)

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password")

        # Ensure password and confirmation match
        if not request.form.get("confirmation") == request.form.get("password"):
            return apology("passwords don't match")

        # Check password meets criteria
        temp = request.form.get("password")
        if not (upper_check(temp) and lower_check(temp) and number_check(temp) and len(temp) > 7):
            return apology("password must have 8 characters, at least one uppercase, one lowercase and one number")

        # store username and hashed password
        username = request.form.get("username")
        hashed = generate_password_hash(request.form.get("password"))

        # insert user info into database
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=username, hash=hashed)

        # Ensure user was successfully added to database
        if not result:
            return apology("Username is not available")

        # Store id in session
        session["user_id"] = db.execute("SELECT id FROM users WHERE username = :username",
                                        username=username)[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # pull stocks for user
    stocks = db.execute("SELECT symbol, SUM(shares) as shares_total \
            FROM transactions WHERE user = :user \
            GROUP BY symbol", user=session["user_id"])

    if request.method == "GET":
        return render_template("sell.html", stocks=stocks)

    # store user input
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    # ensure user selected a symbol
    if not symbol:
        return apology("missing symbol")

    # ensure shares were submitted
    if not shares:
        return apology("missing shares")

    # check user owns that stock
    owned = False

    for stock in stocks:
        owned = owned or stock["symbol"] == symbol

    if not owned:
        return apology("stock not owned")

    # check user has enough shares
    shares_owned = 0

    for stock in stocks:
        if stock["symbol"] == symbol:
            shares_owned = int(stock["shares_total"])
            break

    if int(shares) > shares_owned:
        return apology("too many shares")

    # check user provided a positive number
    if int(shares) < 0:
        return apology("number must be positive")

    # pull stock info
    quote = lookup(request.form.get("symbol"))
    price = quote["price"]

    # update transactions data base
    db.execute("INSERT INTO transactions(user, shares, symbol, price, transacted) \
            VALUES(:user, :shares, :symbol, :price, :transacted)",
               user=session["user_id"],
               shares=int(shares) * -1,
               symbol=symbol,
               price=int(price * 100),
               transacted=datetime.now())

    # update users cash
    db.execute("UPDATE users SET cash = cash + :price WHERE id = :id",
               id=session["user_id"], price=price * int(shares))

    return redirect("/")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

if __name__ == "__main__":
 app.debug = True
 port = int(os.environ.get("PORT", 5000))
 app.run(host="0.0.0.0", port=port)
